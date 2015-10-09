#include "Settings.h"

vbase::SettingsBase::MetaKeyInfo Settings::metaKeyInfoForKey(Settings::KeyEnum key)
{
	auto valueIter = mDefaultValuesHash.find(key);

	if (valueIter != mDefaultValuesHash.end())
		return valueIter.value();

	return vbase::SettingsBase::MetaKeyInfo();
}


Settings::DefaultValuesHash Settings::buildDefaultValuesHash()
{
	DefaultValuesHash dvh;

	dvh[GraphicsWindowIsFullscreen] = { QVariant(false) };

	return dvh;
}


Settings::DefaultValuesHash Settings::mDefaultValuesHash = Settings::buildDefaultValuesHash();
