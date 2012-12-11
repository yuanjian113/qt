/*
 * Target.h
 *
 *  Created on: 2009-2-14
 *      Author: szf
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <QStringList>

/// 目标文件已存在时采取措施
enum FileExistsAction {
	feaOverwrite, 			// 覆盖
	feaIgnore, 				// 跳过
};

typedef struct tagTarget {
	QString desc;
	QString tag;
	QString attr;
	QStringList exts;
	bool selected;

	tagTarget()
	{
	}

	tagTarget(const QString &desc, const QString &tag, const QString &attr,	QStringList exts)
	{
		this->desc = desc;
		this->tag = tag;
		this->attr = attr;
		this->exts = exts;
		this->selected = false;
	}

	/// 是否是超链接
	bool isHyperlink() const {
		return tag.compare("a", Qt::CaseInsensitive) == 0;
	}

	QString toString() const
	{
		QString r = "Description = " + desc
			+ "\nselected = " + (selected ? QString("true") : QString("false"))
			+ "\ntag = " + tag
			+ "\nattr = " + attr
			+ "\nexts = ";
		for(int i = 0; i < exts.size(); i++) {
			r += exts[i];
			if(i < exts.size() - 1)
				r += ";";
		}
		return r;
	}

} Target;

#endif /* TARGET_H_ */
