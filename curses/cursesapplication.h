/*
 * cursesapplication.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESAPPLICATION_H_
#define CURSESAPPLICATION_H_

#include <QtCore/QObject>

class CursesApplication : public QObject
{
    Q_OBJECT
public:
	CursesApplication();
	~CursesApplication();
};

#endif /* CURSESAPPLICATION_H_ */
