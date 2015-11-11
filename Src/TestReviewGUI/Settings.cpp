#include <ValpineBase/SettingsBase.h>

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

	using KeyUpdateType = vbase::SettingsBase::KeyUpdateType;

	dvh[GraphicsWindowIsFullscreen] = { QVariant(false), KeyUpdateType::Instant };

	return dvh;
}


Settings::DefaultValuesHash Settings::mDefaultValuesHash = Settings::buildDefaultValuesHash();
