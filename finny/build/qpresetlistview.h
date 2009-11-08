#ifndef QPRESETLISTVIEW_H
#define QPRESETLISTVIEW_H
//
#include <QListView>
#include <QList>
#include <QModelIndex>
#include <QModelIndexList>
//
class QPresetListView : public QListView
{
Q_OBJECT
public:
	QPresetListView();
	virtual ~QPresetListView();
	
	QModelIndexList selectedIndexes();
};
#endif
