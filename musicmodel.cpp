#include "musicmodel.h"

#include <QDate>
#include <QDebug>
#include <QVariant>
#include <algorithm>

namespace {
bool stringGreater(const QString &lhs, const QString &rhs) { return lhs > rhs; }
bool ullGreater(const QString &lhs, const QString &rhs) {
  return lhs.toULongLong() > rhs.toULongLong();
}
bool floatGreater(const QString &lhs, const QString &rhs) {
  return lhs.toFloat() > rhs.toFloat();
}
bool dateGreater(const QString &lhs, const QString &rhs) {
  return QDate::fromString(lhs, "yyyy-MM-dd") >
         QDate::fromString(rhs, "yyyy-MM-dd");
}
bool stringLess(const QString &lhs, const QString &rhs) { return lhs < rhs; }
bool ullLess(const QString &lhs, const QString &rhs) {
  return lhs.toULongLong() < rhs.toULongLong();
}
bool floatLess(const QString &lhs, const QString &rhs) {
  return lhs.toFloat() < rhs.toFloat();
}
bool dateLess(const QString &lhs, const QString &rhs) {
  return QDate::fromString(lhs, "yyyy-MM-dd") <
         QDate::fromString(rhs, "yyyy-MM-dd");
}
} // namespace

MusicModel::MusicModel(QObject *parent) { qDebug() << __PRETTY_FUNCTION__; }

MusicModel::MusicModel() { qDebug() << __PRETTY_FUNCTION__; }

int MusicModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  // qDebug() << __PRETTY_FUNCTION__;
  return m_tracks.size();
}

int MusicModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  // qDebug() << __PRETTY_FUNCTION__;
  if (m_tracks.isEmpty())
    return 0;
  if (m_tracks.first().isEmpty())
    return 0;
  return m_tracks.first().size();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const {
  // qDebug() << __PRETTY_FUNCTION__;
  if (!index.isValid() || m_tracks.size() <= index.row() ||
      (role != Qt::DisplayRole && role != Qt::EditRole)) {
    return QVariant();
  }

  return m_tracks.at(index.row()).at(index.column());
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
  // qDebug() << __PRETTY_FUNCTION__;
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
  // qDebug() << __PRETTY_FUNCTION__;
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Vertical) {
    return section;
  }
  if (!(section > m_headers.size()))
    return QVariant(m_headers.at(section));
  else
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const {
  // qDebug() << __PRETTY_FUNCTION__;
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);
  if (index.isValid()) {

    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  return flags;
}

void MusicModel::insertRow(int row, const QStringList &items) {
  // qDebug() << __PRETTY_FUNCTION__;
  if (row > rowCount(QModelIndex()))
    return;
  if (items.empty())
    return;
  emit beginInsertRows(QModelIndex(), row, row);
  m_tracks.insert(row, items);
  emit endInsertRows();
}

void MusicModel::setHorizontalHeaderLabels(const QStringList &labels) {
  // qDebug() << __PRETTY_FUNCTION__;
  if (!labels.empty())
    m_headers = labels;
}

// void MusicModel::sort(int column, Qt::SortOrder order) {

//  QModelIndex tempIndex;
//  int row = 0;
//  while (!tempIndex.data().isNull()) {
//    tempIndex = index(++row, column);
//  }
//  switch (order) {
//  case Qt::AscendingOrder: {
//    if (tempIndex.data().canConvert(QMetaType::QDate))
//      std::sort(m_tracks.begin(), m_tracks.end(),
//                [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                  return dateGreater(lhs.at(column), rhs.at(column));
//                });
//    else {
//      if (tempIndex.data().canConvert(QMetaType::Float))
//        std::sort(m_tracks.begin(), m_tracks.end(),
//                  [column](const TrackData &lhs, const TrackData &rhs) -> bool
//                  {
//                    return floatGreater(lhs.at(column), rhs.at(column));
//                  });
//      else {
//        if (tempIndex.data().canConvert(QMetaType::ULongLong))
//          std::sort(
//              m_tracks.begin(), m_tracks.end(),
//              [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                return ullGreater(lhs.at(column), rhs.at(column));
//              });
//        else {
//          if (tempIndex.data().canConvert(QMetaType::QString))
//            std::sort(
//                m_tracks.begin(), m_tracks.end(),
//                [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                  return stringGreater(lhs.at(column), rhs.at(column));
//                });
//        }
//      }
//    }
//    break;
//  }
//  case Qt::DescendingOrder: {
//    if (tempIndex.data().canConvert(QMetaType::QDate))
//      std::sort(m_tracks.begin(), m_tracks.end(),
//                [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                  return dateLess(lhs.at(column), rhs.at(column));
//                });
//    else {
//      if (tempIndex.data().canConvert(QMetaType::Float))
//        std::sort(m_tracks.begin(), m_tracks.end(),
//                  [column](const TrackData &lhs, const TrackData &rhs) -> bool
//                  {
//                    return floatLess(lhs.at(column), rhs.at(column));
//                  });
//      else {
//        if (tempIndex.data().canConvert(QMetaType::ULongLong))
//          std::sort(
//              m_tracks.begin(), m_tracks.end(),
//              [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                return ullLess(lhs.at(column), rhs.at(column));
//              });
//        else {
//          if (tempIndex.data().canConvert(QMetaType::QString))
//            std::sort(
//                m_tracks.begin(), m_tracks.end(),
//                [column](const TrackData &lhs, const TrackData &rhs) -> bool {
//                  return stringLess(lhs.at(column), rhs.at(column));
//                });
//        }
//      }
//    }
//    break;
//  }
//  }

//  dataChanged(createIndex(0, 0),
//              createIndex(rowCount(QModelIndex()),
//              columnCount(QModelIndex())));
//}
