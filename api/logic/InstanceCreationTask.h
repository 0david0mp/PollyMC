#pragma once

#include "tasks/Task.h"
#include "multimc_logic_export.h"
#include "net/NetJob.h"
#include <QUrl>
#include "settings/SettingsObject.h"
#include "BaseVersion.h"

class MULTIMC_LOGIC_EXPORT InstanceCreationTask : public Task
{
	Q_OBJECT
public:
	explicit InstanceCreationTask(SettingsObjectPtr settings, const QString & stagingPath, BaseVersionPtr version, const QString &instName,
		const QString &instIcon, const QString &instGroup);

protected:
	//! Entry point for tasks.
	virtual void executeTask() override;

private: /* data */
	SettingsObjectPtr m_globalSettings;
	QString m_stagingPath;
	BaseVersionPtr m_version;
	QString m_instName;
	QString m_instIcon;
	QString m_instGroup;
};

