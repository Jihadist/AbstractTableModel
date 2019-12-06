#pragma once

#include <QSortFilterProxyModel>

class MusicSortFilterProxyModel : public QSortFilterProxyModel {
public:
  MusicSortFilterProxyModel();
  MusicSortFilterProxyModel(QObject *parent = 0);
  bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};
