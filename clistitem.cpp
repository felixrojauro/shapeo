#include "clistitem.h"

CListItem::CListItem(QObject *pParent) :
    QObject(pParent),
    m_strImgSource("dummy"),
    m_strName("dummy")
{
}

CListItem::CListItem(const CListItem &pOtherItem) :
    QObject(pOtherItem.parent())
{
    m_strName = pOtherItem.m_strName;
    m_strImgSource = pOtherItem.m_strImgSource;
}

CListItem::~CListItem()
{
    // Nothing
}
