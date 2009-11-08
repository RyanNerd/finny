#include "qpresetlistview.h"
//
QPresetListView::QPresetListView(  ) 
	: QListView()
{
	// TODO
}
//
QPresetListView::~QPresetListView()
{
}

QModelIndexList QPresetListView::selectedIndexes()
{
	return QListView::selectedIndexes();
}
//