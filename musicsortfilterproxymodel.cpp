#include "musicsortfilterproxymodel.h"
//#include "musicmodel.h"
#include <QDate>
#include <QDebug>
#include <QMetaType>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
MusicSortFilterProxyModel::MusicSortFilterProxyModel() = default;

MusicSortFilterProxyModel::MusicSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool MusicSortFilterProxyModel::lessThan(const QModelIndex &left,
                                         const QModelIndex &right) const {
  int MetaTypeMoney = qRegisterMetaType<money>();
  int MetaTypeUnsigned = qRegisterMetaType<counter>();

  QVariant lhs = sourceModel()->data(left);
  QVariant rhs = sourceModel()->data(right);
  // Date format is ("yyyy-MM-dd")

  if (lhs.canConvert(QMetaType::QDate)) {
    static const QRegularExpression datePattern(
        "^((((19|20)(([02468][048])|([13579][26])).02.29))|((20[0-9][0-9])|(19["
        "0-9][0-9])).((((0[1-9])|(1[0-2])).((0[1-9])|(1[0-9])|(2[0-8])))|((((0["
        "13578])|(1[02])).31)|(((0[1,3-9])|(1[0-2])).(29|30)))))$");
    const QRegularExpressionMatch match = datePattern.match(lhs.toString());
    if (match.hasMatch()) {
      qDebug() << "Date compare" << lhs << ":" << rhs;
      return lhs.toDate() < rhs.toDate();
    }
  }

  if (lhs.type() == QVariant::Double) {
    qDebug() << "Double compare" << lhs.type() << " " << lhs << ":" << rhs;
    return lhs.toString().remove(QRegExp(" .*")).toInt() <
           rhs.toString().remove(QRegExp(" .*")).toInt();
  }
  if (lhs.type() == QVariant::ULongLong) {
    qDebug() << "ULongLong compare" << lhs.type() << " " << lhs << ":" << rhs;
    return lhs.toULongLong() < rhs.toULongLong();
  }
  qDebug() << "String compare" << lhs.type() << " " << lhs << ":" << rhs;
  return lhs.toString() < rhs.toString();
}
