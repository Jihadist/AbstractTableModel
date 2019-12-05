#pragma once

#include <QStandardItemModel>

class StandardTrackModel : public QStandardItemModel {
public:
  StandardTrackModel();
  enum Role { DateRole = Qt::UserRole, MoneyRole, CountRole, NameRole };
};
