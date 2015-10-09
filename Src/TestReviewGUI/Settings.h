#ifndef Settings_h
#define Settings_h

#include <QtCore/QObject>
#include <ValpineBase/Settings.h>

class Settings : public QObject
{
	Q_OBJECT

public:
	enum KeyEnum
	{
		GraphicsWindowIsFullscreen = 1001
	};

	Q_ENUMS(KeyEnum)

	static vbase::SettingsBase::MetaKeyInfo metaKeyInfoForKey(KeyEnum key);



private:
	using DefaultValuesHash = QHash<KeyEnum, vbase::SettingsBase::MetaKeyInfo>;
	static DefaultValuesHash mDefaultValuesHash;
	static DefaultValuesHash buildDefaultValuesHash();
};

#endif

