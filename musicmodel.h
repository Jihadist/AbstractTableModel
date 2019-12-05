#pragma once

#include <QAbstractTableModel>
#include <QList>

class MusicModel : public QAbstractTableModel {
  Q_OBJECT
public:
  MusicModel(QObject *parent = 0);
  MusicModel();

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

  void insertRow(int row, const QStringList &items);

  void setHorizontalHeaderLabels(const QStringList &labels);
  //  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

  //  virtual bool insertRows (int position, int rows, const QModelIndex &
  //  parent = QModelIndex()); virtual bool removeRows (int position, int rows,
  //  const QModelIndex & parent = QModelIndex());

private:
  QStringList m_columns;
  QStringList m_headers;

  typedef QStringList TrackData;
  typedef QList<TrackData> Tracks;
  Tracks m_tracks;
};
