#pragma once

#include <QSortFilterProxyModel>

// Class for sorting multiple values in csv table but doesnt work now
class MusicSortFilterProxyModel : public QSortFilterProxyModel {
public:
  MusicSortFilterProxyModel();
  MusicSortFilterProxyModel(QObject *parent = 0);
  bool lessThan(const QModelIndex &left,
                const QModelIndex &right) const override;

  struct money {
    double d;
  };
  struct counter {
    unsigned long long ull;
  };
};
