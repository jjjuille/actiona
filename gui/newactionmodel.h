/*
	Actiona
	Copyright (C) 2005-2016 Jonathan Mercier-Ganady

	Actiona is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actiona is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#ifndef NEWACTIONMODEL_H
#define NEWACTIONMODEL_H

#include <QStandardItemModel>

class NewActionModel : public QStandardItemModel
{
	Q_OBJECT

public:
	enum NewActionRole
	{
		ActionIdRole = Qt::UserRole
	};

    explicit NewActionModel(QObject *parent = 0);

protected:
	Qt::DropActions supportedDropActions() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;

private:
    Q_DISABLE_COPY(NewActionModel)
};

#endif // NEWACTIONMODEL_H