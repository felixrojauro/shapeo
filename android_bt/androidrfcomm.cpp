/**
  @file
  @author Stefan Frings
*/

#include "androidrfcomm.h"
#include <QThread>
#include <QDateTime>
#include <QDebug>

AndroidRfComm::AndroidRfComm() {
    timeout=false;
    useLatin1=false;
	sendTerminator=QString("$");
	receiveTerminator=QString("$");

    qDebug("Opening bluetooth adapter");
    adapter=QAndroidJniObject::callStaticObjectMethod("android/bluetooth/BluetoothAdapter","getDefaultAdapter","()Landroid/bluetooth/BluetoothAdapter;");
    check("BluetoothAdapter.getDefaultAdapter()",adapter);

    // Check if the adapter is enabled and eventually wait until it is ready to be used
    isEnabled();
}

AndroidRfComm::~AndroidRfComm() {
    disconnect();
}

void AndroidRfComm::check(const char* method) {
	QAndroidJniEnvironment env;
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
        qCritical("Exception in %s",method);
    }
}

void AndroidRfComm::check(const char* method, const QAndroidJniObject& obj) {
	QAndroidJniEnvironment env;

	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
        qCritical("Exception in %s",method);
    }
    else if (!obj.isValid()) {
        qCritical("Invalid object in %s",method);
    }
}

bool AndroidRfComm::isEnabled() {
    if (!adapter.isValid()) {
        qWarning("Cannot query bluetooth status, there is no bluetooth adapter");
        return false;
    }

    jboolean enabled=adapter.callMethod<jboolean>("isEnabled");
    check("BluetoothAdapter.isEnabled()");

    // If the adapter has just been enabled, then wait until it is ready to be used
    if (enabled) {
        jint state=adapter.callMethod<jint>("getState");
        check("BluetoothAdapter.getState()");
        while (state!=12) {
            qWarning("Waiting 1 sec. for the bluetooth adapter to become ready");
            QThread::msleep(1000);
            state=adapter.callMethod<jint>("getState");
            check("BluetoothAdapter.getState()");
        }
    }
    if (!enabled) {
        qWarning("Bluetooth adapter is disabled");
    }
    return enabled;
}

QMap<QString,QString> AndroidRfComm::getPairedDevices() {
    QMap<QString,QString> result;

    if (!adapter.isValid()) {
        qWarning("Cannot list paired devices, there is no bluetooth adapter");
        return result;
    }

    qDebug("Querying paired bluetooth devices");
    QAndroidJniObject pairedDevicesSet=adapter.callObjectMethod("getBondedDevices","()Ljava/util/Set;"); // Set<BluetoothDevice>
    check("BluetoothAdapter.getBondedDevices()",pairedDevicesSet);

    jint size=pairedDevicesSet.callMethod<jint>("size");
    check("Set<BluetoothDevice>.size()");
    qDebug("Found %i paired devices",size);

    if (size>0) {
        QAndroidJniObject iterator=pairedDevicesSet.callObjectMethod("iterator","()Ljava/util/Iterator;"); // Iterator<BluetoothDevice>
        check("Set<BluetoothDevice>.iterator()",iterator);
        for (int i=0; i<size; i++) {
            QAndroidJniObject dev=iterator.callObjectMethod("next","()Ljava/lang/Object;"); // BluetoothDevice
            check("Iterator<BluetoothDevice>.next()",dev);
            QString address=dev.callObjectMethod("getAddress","()Ljava/lang/String;").toString();
            QString name=dev.callObjectMethod("getName","()Ljava/lang/String;").toString();
            result.insert(address,name);
        }
    }
    return result;
}

void AndroidRfComm::connect(const QString& nameOrAddress) {
//	JNIEnv* jniEnv;
//	if (QAndroidJniEnvironment::javaVM()->GetEnv((void**)&jniEnv, JNI_VERSION_1_6) < 0) {
//		if (QAndroidJniEnvironment::javaVM()->AttachCurrentThread(&jniEnv, NULL) < 0) {
////			__android_log_print(ANDROID_LOG_ERROR, "Qt", "AttachCurrentThread failed");
//			jniEnv = 0;
//			return;
//		}
////		attached = true;

//	}
//	*env = *jniEnv;
		qDebug()<<"@#@#@#@# ATTACHED CURRENT THREAD!";
	if (!adapter.isValid()) {
        qCritical("Cannot open connection, there is no bluetooth adapter");
        return;
    }

    // Eventually cancel pending discovery because that conflicts with opening a device
    jboolean discovering=adapter.callMethod<jboolean>("isDiscovering");
    check("BluetoothDevice.isDiscovering()");
    if (discovering) {
        qWarning("Cancelling pending bluetooth discovery");
        adapter.callMethod<jboolean>("cancelDiscovery");
        check("BluetoothDevice.cancelDiscovery()");
    }

    qDebug("Search bluetooth device %s",qPrintable(nameOrAddress));
    bool found=false;
    QAndroidJniObject pairedDevicesSet=adapter.callObjectMethod("getBondedDevices","()Ljava/util/Set;"); // Set<BluetoothDevice>
    check("BluetoothAdapter.getBondedDevices()",pairedDevicesSet);
    jint size=pairedDevicesSet.callMethod<jint>("size");
    check("Set<BluetoothDevice>.size()");
    if (size>0) {
        QAndroidJniObject iterator=pairedDevicesSet.callObjectMethod("iterator","()Ljava/util/Iterator;"); // Iterator<BluetoothDevice>
        check("Set<BluetoothDevice>.iterator()",iterator);
        for (int i=0; i<size; i++) {
            QAndroidJniObject dev=iterator.callObjectMethod("next","()Ljava/lang/Object;"); // BluetoothDevice
            check("Iterator<BluetoothDevice>.next()",dev);
            QString adr=dev.callObjectMethod("getAddress","()Ljava/lang/String;").toString();
            QString name=dev.callObjectMethod("getName","()Ljava/lang/String;").toString();
            if (nameOrAddress.compare(adr,Qt::CaseInsensitive)==0 || nameOrAddress.compare(name,Qt::CaseInsensitive)==0) {
                device=dev;
                found=true;
                break;
            }
        }
    }
    if (!found) {
        qCritical("Bluetooth device not found");
        return;
    }

    qDebug("Open connection");
    QAndroidJniObject string=QAndroidJniObject::fromString("00001101-0000-1000-8000-00805F9B34FB");
    QAndroidJniObject uuid=QAndroidJniObject::callStaticObjectMethod("java/util/UUID","fromString","(Ljava/lang/String;)Ljava/util/UUID;",string.object<jstring>());
    check("UUID.fromString()",uuid);
    socket=device.callObjectMethod("createRfcommSocketToServiceRecord","(Ljava/util/UUID;)Landroid/bluetooth/BluetoothSocket;",uuid.object<jobject>());
    check("UUID.createRfcommSocketToServiceRecord()",socket);
    socket.callMethod<void>("connect");
    check("BluetoothSocket.connect()");
    jboolean connected=socket.callMethod<jboolean>("isConnected");
    check("BluetoothSocket.isConnected()");
    if (connected) {
        istream=socket.callObjectMethod("getInputStream","()Ljava/io/InputStream;");
        check("BluetoothSocket.getInputStream()",istream);
        ostream=socket.callObjectMethod("getOutputStream","()Ljava/io/OutputStream;");
        check("BluetoothSocket.getOutputStream()",ostream);
    }
    else {
        qCritical("Cannot connect to the bluetooth device");
    }
}

bool AndroidRfComm::isConnected() {
    if (socket.isValid()) {
        jboolean connected=socket.callMethod<jboolean>("isConnected");
        check("BluetoothSocket.isConnected()");
        return connected;
    }
    else {
        return false;
    }
}

void AndroidRfComm::send(const QByteArray& data) {
	QAndroidJniEnvironment env;

	if (!ostream.isValid()) {
       qCritical("Cannot send, bluetooth socket is not connected");
       return;
    }
    int size=data.length();
    const char* rawData=data.constData();
    qDebug("Sending %i bytes over bluetooth",size);
	jbyteArray nativeData = env->NewByteArray(size);
	env->SetByteArrayRegion(nativeData, 0, size, (jbyte*)rawData);
    ostream.callMethod<void>("write", "([BII)V", nativeData, (jint)0, (jint)size);
    check("OutputStream.write()");
	env->DeleteLocalRef(nativeData);
}

void AndroidRfComm::sendLine(const QString& text) {
    QByteArray data=useLatin1?text.toLatin1():text.toUtf8();
    data.append(sendTerminator);
    send(data);
}

int AndroidRfComm::available() {
    if (istream.isValid()) {
        jint bytes=istream.callMethod<jint>("available");
        check("InputStream.available()");
        return bytes+buffer.length();
    }
    else {
        return buffer.length();
    }
}

int AndroidRfComm::readIntoBuffer() {
	QAndroidJniEnvironment env;

	if (!istream.isValid()) {
        return 0;
    }
	jint size=istream.callMethod<jint>("available");
    check("InputStream.available()");
    if (size>0) {
        char* rawData=new char[size];
		jbyteArray nativeData = env->NewByteArray(size);
        jint numRead=istream.callMethod<jint>("read", "([BII)I", nativeData, (jint)0, (jint)size);
		check("InputStream.read()");
		env->GetByteArrayRegion(nativeData, 0, size, (jbyte*)rawData);
		buffer.append(rawData,numRead);
		env->DeleteLocalRef(nativeData);
        delete rawData;
        return numRead;
    }
    else {
        return 0;
    }
}

QByteArray AndroidRfComm::receive(const int maxNumOfBytes, const int waitMilliSeconds) {
    qint64 maxTime=QDateTime::currentMSecsSinceEpoch()+waitMilliSeconds;
    timeout=false;
    while (buffer.length()<maxNumOfBytes) {
        if (QDateTime::currentMSecsSinceEpoch()>maxTime) {
            timeout=true;
            break;
        }
        QThread::msleep(10);
        readIntoBuffer();
    }
    // Truncate the result and keep only the remainder in the buffer
    QByteArray result=buffer.left(maxNumOfBytes);
    buffer.remove(0,result.length());
    return result;
}

QString AndroidRfComm::receiveLine(const int maxCharacters, const int waitMilliSeconds) {
    qint64 maxTime=QDateTime::currentMSecsSinceEpoch()+waitMilliSeconds;
    // Receive repeatedly
    timeout=false;
    QString line=useLatin1?QString::fromLatin1(buffer):QString::fromUtf8(buffer);
    int posi=line.indexOf(receiveTerminator);
    while (posi<0 && line.length()<maxCharacters+receiveTerminator.length() && !timeout) {
        int numRead=0;
        while (numRead==0) {
            if (QDateTime::currentMSecsSinceEpoch()>maxTime) {
                timeout=true;
                break;
            }
            QThread::msleep(10);
            numRead=readIntoBuffer();
        }
        line=useLatin1?QString::fromLatin1(buffer):QString::fromUtf8(buffer);
        posi=line.indexOf(receiveTerminator);
    }
    //  Truncate the line
    if (posi>=0 && posi<=maxCharacters) {
        // The line is terminated
        line=line.left(posi+receiveTerminator.length());
    }
    else {
        // The line is not terminated or longer than allowed
        line=line.left(maxCharacters);
    }
    // Remove the line from the buffer
	qDebug()<<"got lane! "<<line;
    buffer.remove(0,line.toUtf8().length());
    // Remove the terminator from the line, if present
    if (posi>=0 && posi<=maxCharacters) {
        line=line.left(posi);
    }
    return line;
}

bool AndroidRfComm::hasTimeout() {
    return timeout;
}

void AndroidRfComm::disconnect() {
    qDebug("Closing bluetooth connection");
    if (istream.isValid()) {
        istream.callMethod<void>("close");
        check("InputStream.close()");
    }
    if (ostream.isValid()) {
        ostream.callMethod<void>("close");
        check("OutputStream.close()");
    }
    if (socket.isValid()) {
        socket.callMethod<void>("close");
        check("BluetoothSocket.close()");
    }
}

void AndroidRfComm::setLatin1Encoding(const bool enable) {
    useLatin1=enable;
}

bool AndroidRfComm::getLatin1Encoding() {
    return useLatin1;
}

void AndroidRfComm::setSendTerminator(const QString& s) {
    sendTerminator=s;
}

QString AndroidRfComm::getSendTerminator() {
    return sendTerminator;
}

void AndroidRfComm::setReceiveTerminator(const QString& s) {
    receiveTerminator=s;
}

QString AndroidRfComm::getReceiveTerminator() {
    return receiveTerminator;
}
