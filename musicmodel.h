#pragma once

#include <QAbstractTableModel>
#include <QList>

class MusicModel : public QAbstractTableModel {
  Q_OBJECT
public:
  MusicModel(QObject *parent = 0);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  // int rowCount() const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  // int columnCount() const;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  bool removeRows(int position, int rows,
                  const QModelIndex &index = QModelIndex()) override;
  // bool removeRows(int position, int rows);
  void insertRow(int row, const QStringList &items);

  bool removeColumns(int column, int count,
                     const QModelIndex &parent = QModelIndex()) override;

  void setHorizontalHeaderLabels(const QStringList &labels);

  bool hideUnusedColumns();
  // QVector<int> positionUnusedColumns();
  const QStringList getUnusedColumns();
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
