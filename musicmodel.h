#pragma once

#include <QAbstractTableModel>
#include <QList>

class MusicModel : public QAbstractTableModel {
  Q_OBJECT
public:
  typedef QList<QVariant> TrackData;
  typedef QList<TrackData> Tracks;

public:
  MusicModel(QObject *parent = 0);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  bool removeRows(int position, int rows,
                  const QModelIndex &index = QModelIndex()) override;
  void insertRow(int row, const TrackData &items);

  bool removeColumns(int column, int count,
                     const QModelIndex &parent = QModelIndex()) override;

  void setHorizontalHeaderLabels(const QStringList &labels);

  bool hideUnusedColumns();

private:
  // QStringList m_columns;
  QStringList m_headers;

  Tracks m_tracks;
};
