#pragma once

#include "tasks/Task.h"
#include "multimc_logic_export.h"
#include "net/NetJob.h"
#include <QUrl>
#include <QFuture>
#include <QFutureWatcher>
#include "settings/SettingsObject.h"
#include "QObjectPtr.h"

class BaseInstanceProvider;
namespace Curse
{
	class FileResolvingTask;
}

class MULTIMC_LOGIC_EXPORT InstanceImportTask : public Task
{
	Q_OBJECT
public:
	explicit InstanceImportTask(SettingsObjectPtr settings, const QUrl sourceUrl, BaseInstanceProvider * target, const QString &instName,
		const QString &instIcon, const QString &instGroup);

protected:
	//! Entry point for tasks.
	virtual void executeTask() override;

private:
	void extractAndTweak();
	void processMultiMC(const QFileInfo &config);
	void processCurse(const QFileInfo &manifest);

private slots:
	void downloadSucceeded();
	void downloadFailed(QString reason);
	void downloadProgressChanged(qint64 current, qint64 total);
	void extractFinished();
	void extractAborted();
	void curseResolvingSucceeded();
	void curseResolvingFailed(QString reason);

private: /* data */
	SettingsObjectPtr m_globalSettings;
	NetJobPtr m_filesNetJob;
	shared_qobject_ptr<Curse::FileResolvingTask> m_curseResolver;
	QUrl m_sourceUrl;
	BaseInstanceProvider * m_target;
	QString m_archivePath;
	bool m_downloadRequired = false;
	QString m_packRoot;
	QString m_instName;
	QString m_instIcon;
	QString m_instGroup;
	QString m_stagingPath;
	QFuture<QStringList> m_extractFuture;
	QFutureWatcher<QStringList> m_extractFutureWatcher;
};
