#include "musicmodel.h"

#include <QDate>
#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <algorithm>

MusicModel::MusicModel(QObject *parent) : QAbstractTableModel(parent) {}

int MusicModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  // qDebug() << __PRETTY_FUNCTION__;
  return m_tracks.size();
}

int MusicModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  if (m_tracks.isEmpty())
    return 0;
  if (m_tracks.first().isEmpty())
    return 0;
  return m_tracks.first().size();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || m_tracks.size() <= index.row() ||
      (role != Qt::DisplayRole && role != Qt::EditRole)) {
    return QVariant();
  }

  return m_tracks.at(index.row()).at(index.column());
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
  if (!index.isValid() || role != Qt::EditRole ||
      m_tracks.size() <= index.row()) {
    return false;
  }

  m_tracks[index.row()][index.column()] = value.toString();
  emit dataChanged(index, index);

  return true;
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Vertical) {
    return section;
  }
  if (!(section > m_headers.size() - 1))
    return QVariant(m_headers.at(section));

  return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);
  if (index.isValid()) {

    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  return flags;
}

bool MusicModel::removeRows(int row, int count, const QModelIndex &index) {
  Q_UNUSED(index)
  if ((count < 1) || (row < 0) || ((row + count) > rowCount()))
    return false;
  if (m_tracks.empty())
    return false;
  beginRemoveRows(QModelIndex(), row, row + count - 1);

  for (auto pos = row; pos < row + count; ++pos) {
    m_tracks.removeAt(row);
  }

  endRemoveRows();
  return true;
}

void MusicModel::insertRow(int row, const TrackData &items) {

  if (row > rowCount())
    return;
  if (items.empty())
    return;
  emit beginInsertRows(QModelIndex(), row, row);
  m_tracks.insert(row, items);
  emit endInsertRows();
}

bool MusicModel::removeColumns(int column, int count,
                               const QModelIndex &parent) {
  Q_UNUSED(parent)
  if ((count < 1) || (column < 0) || ((column + count) > columnCount()))
    return false;

  emit beginRemoveColumns(QModelIndex(), column, column + count - 1);
  for (auto &row : m_tracks) {
    if (!row.isEmpty()) {
      for (auto pos = column; pos < column + count; ++pos) {
        if (column < row.size())
          row.removeAt(column);
      }
    }
  }
  for (auto pos = column; pos < column + count; ++pos) {
    if (column < m_headers.size()) {
      m_headers.removeAt(column);
    }
  }
  qDebug() << "Removed";
  emit endRemoveColumns();
  return true;
}

void MusicModel::setHorizontalHeaderLabels(const QStringList &labels) {
  // qDebug() << __PRETTY_FUNCTION__;
  if (!labels.empty())
    m_headers = labels;
}

bool MusicModel::hideUnusedColumns() {
  TrackData *tempString = &m_tracks.first();
  int len = tempString->length();
  for (int index = 0; index != len; ++index) {
    qDebug() << "Enter loop at index: " << index;
    if (tempString->at(index).toString().isEmpty()) {
      removeColumns(index, 1);
      qDebug() << "index" << index;
      len = tempString->length();
      --index;
    }
  }
  return true;
}
