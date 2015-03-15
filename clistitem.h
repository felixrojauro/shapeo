#ifndef CLISTITEM_H
#define CLISTITEM_H

#include <QObject>

class CListItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString imgSource READ getImgSource WRITE setImgSource NOTIFY imgSourceChanged)

public:
    explicit CListItem(QObject *pParent = 0);
    CListItem(const CListItem &pOtherItem);     //!< copy constructor needed to register Q_DECLARE_METATYPE
    virtual ~CListItem();

    inline QString getName() const { return m_strName; }
    inline void setName(QString a_strNewName) { m_strName = a_strNewName; }

    inline QString getImgSource() const { return m_strImgSource; }
    inline void setImgSource(QString a_strNewImgSource) { m_strImgSource = a_strNewImgSource; }

signals:
    void nameChanged(QString a_strNewName);
    void imgSourceChanged(QString a_strNewImgSource);

private:
    QString m_strName;
    QString m_strImgSource;

};

Q_DECLARE_METATYPE( CListItem )

#endif // CLISTITEM_H
