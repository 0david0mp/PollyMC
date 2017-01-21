#pragma once

#include "BaseWizardPage.h"
#include <BaseVersion.h>
#include <QObjectPtr.h>
#include <java/JavaChecker.h>
#include <QIcon>

class QLineEdit;
class VersionSelectWidget;
class QSpinBox;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QGridLayout;
class QLabel;
class QToolButton;

class JavaWizardPage : public BaseWizardPage
{
	Q_OBJECT;
public:
	explicit JavaWizardPage(QWidget *parent = Q_NULLPTR);

	virtual ~JavaWizardPage()
	{
	};

	bool wantsRefreshButton() override;
	void refresh() override;
	void initializePage() override;
	bool validatePage() override;

	enum class JavaStatus
	{
		NotSet,
		Pending,
		Good,
		DoesNotExist,
		DoesNotStart,
		ReturnedInvalidData
	} javaStatus = JavaStatus::NotSet;

protected slots:
	void memoryValueChanged(int);
	void javaPathEdited(const QString &path);
	void javaVersionSelected(BaseVersionPtr version);
	void on_javaBrowseBtn_clicked();
	void on_javaStatusBtn_clicked();
	void checkFinished(JavaCheckResult result);

protected: /* methods */
	void checkJavaPathOnEdit(const QString &path);
	void checkJavaPath(const QString &path);
	void setJavaStatus(JavaStatus status);
	void setupUi();
	void retranslate() override;

private: /* data */
	VersionSelectWidget *m_versionWidget = nullptr;
	QVBoxLayout *m_verticalLayout = nullptr;

	QLineEdit * m_javaPathTextBox = nullptr;
	QPushButton * m_javaBrowseBtn = nullptr;
	QToolButton * m_javaStatusBtn = nullptr;
	QHBoxLayout *m_horizontalLayout = nullptr;

	QGroupBox *m_memoryGroupBox = nullptr;
	QGridLayout *m_gridLayout_2 = nullptr;
	QSpinBox *m_maxMemSpinBox = nullptr;
	QLabel *m_labelMinMem = nullptr;
	QLabel *m_labelMaxMem = nullptr;
	QSpinBox *m_minMemSpinBox = nullptr;
	QLabel *m_labelPermGen = nullptr;
	QSpinBox *m_permGenSpinBox = nullptr;
	QIcon goodIcon;
	QIcon yellowIcon;
	QIcon badIcon;

	int observedMinMemory = 0;
	int observedMaxMemory = 0;
	int observedPermGenMemory = 0;
	QString queuedCheck;
	uint64_t m_availableMemory = 0ull;
	shared_qobject_ptr<JavaChecker> m_checker;
	JavaCheckResult m_result;
};

