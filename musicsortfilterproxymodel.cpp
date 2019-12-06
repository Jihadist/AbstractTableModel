#include "musicsortfilterproxymodel.h"
//#include "musicmodel.h"
#include <QDate>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
MusicSortFilterProxyModel::MusicSortFilterProxyModel() = default;

MusicSortFilterProxyModel::MusicSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool MusicSortFilterProxyModel::lessThan(const QModelIndex &left,
                                         const QModelIndex &right) const {

  QVariant lhs = sourceModel()->data(left).toString();
  QVariant rhs = sourceModel()->data(right).toString();
  // Date format is ("yyyy-MM-dd")

  if (lhs.canConvert(QMetaType::QDate)) {
    static const QRegularExpression datePattern(
        "^((((19|20)(([02468][048])|([13579][26])).02.29))|((20[0-9][0-9])|(19["
        "0-9][0-9])).((((0[1-9])|(1[0-2])).((0[1-9])|(1[0-9])|(2[0-8])))|((((0["
        "13578])|(1[02])).31)|(((0[1,3-9])|(1[0-2])).(29|30)))))$");
    const QRegularExpressionMatch match = datePattern.match(lhs.toString());
    if (match.hasMatch()) {
      // qDebug() << "Date compare" << lhs << ":" << rhs;
      return lhs.toDate() < rhs.toDate();
    }
  }
  if (lhs.canConvert(QMetaType::Double)) {
    // qDebug() << "Double compare" << lhs << ":" << rhs;
    return lhs.toDouble() < rhs.toDouble();
  }
  if (lhs.canConvert(QMetaType::ULongLong)) {
    // qDebug() << "ULongLong compare" << lhs << ":" << rhs;
    return lhs.toULongLong() < rhs.toULongLong();
  }
  // qDebug() << "String compare" << lhs << ":" << rhs;
  return lhs.toString() < rhs.toString();
}
