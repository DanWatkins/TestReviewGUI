#ifndef Settings_h
#define Settings_h

#include <QtCore/QObject>

class Settings : public QObject
{
	Q_OBJECT

public:
	enum KeyEnum
	{
		GraphicsWindowIsFullscreen = 1001
	};

	Q_ENUMS(KeyEnum)
};

#endif

