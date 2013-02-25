// Default empty project template
#include "PointClient.hpp"

#include <QObject>
#include <QIODevice>
#include <QDir>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/GroupDataModel>
#include <bb/data/JsonDataAccess>
#include <bb/system/SystemToast>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::data;

PointClient::PointClient(bb::cascades::Application *app) :
		QObject(app) {
	// Load the QML document
	QmlDocument *qml = QmlDocument::create("asset:///main.qml");

	// Expose this class to QML so that we can call its functions from there
	qml->setContextProperty("app", this);

	// Retrieve the root node
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	// Retrieve the activity indicator from QML so that we can start
	// and stop it from C++
	mActivityIndicator = root->findChild<ActivityIndicator*>("indicator");

	// Retrieve the list so we can set the data model on it once
	// we retrieve it
	mListView = root->findChild<ListView*>("list");

	// Create a network access manager and connect a custom slot to its
	// finished signal
	mNetworkAccessManager = new QNetworkAccessManager(this);

	bool result = connect(mNetworkAccessManager,
			SIGNAL(finished(QNetworkReply*)), this,
			SLOT(requestFinished(QNetworkReply*)));

	// Displays a warning message if there's an issue connecting the signal
	// and slot. This is a good practice with signals and slots as it can
	// be easier to mistype a slot or signal definition
	Q_ASSERT(result);
	Q_UNUSED(result);

	// Create a file in the application's data directory
	mFile = new QFile(QDir::homePath() + "/users.json");

	// set created root object as a scene
	app->setScene(root);
}

void PointClient::initiateRequest() {
	// Start the activity indicator
	mActivityIndicator->start();

	// Create and send the network request
	QNetworkRequest request = QNetworkRequest();
	QUrl url("http://mighty-beyond-5329.herokuapp.com/users/1.json");
	request.setUrl(
			QUrl("http://mighty-beyond-5329.herokuapp.com/users/1.json"));
	mNetworkAccessManager->get(request);
}

void PointClient::requestFinished(QNetworkReply* reply) {
	SystemToast *toast = new SystemToast(this);
	// Check the network reply for errors
	if (reply->error() == QNetworkReply::NoError) {
		// Open the file and print an error if the file cannot be opened
		if (!mFile->open(QIODevice::ReadWrite)) {
			toast->setBody("\n Failed to open file");
			toast->show();
			return;
		}

		// Write to the file using the reply data and close the file
		mFile->write("[");
		mFile->write(reply->readAll());
		mFile->write("]");
		mFile->flush();
		mFile->close();

		if (!mFile->open(QIODevice::ReadWrite)) {
			toast->setBody("\n Failed to open file");
			toast->show();
			return;
		}

		QTextStream batStream(mFile);
		QString line;
		while (!batStream.atEnd()) {
			line = batStream.readLine();
			toast->setBody(line);
			toast->show();
		}
		mFile->close();

		// Create the data model, specifying sorting keys of "firstName" and "lastName"
		GroupDataModel *usersModel = new GroupDataModel(
				QStringList() << "created_at" << "id" << "phoneNumber"
						<< "updated_at" << "userId" << "username" << "groups");
		// Create a JsonDataAccess object and load the .json file. The
		// QDir::currentPath() function returns the current working directory
		// for the app.
		JsonDataAccess jda;
		QVariant list = jda.load(QDir::homePath() + "/users.json");

		// Determine if an error occurred during the load() operation
		if (jda.hasError()) {
			// Retrieve the error
			DataAccessError theError = jda.error();

			// Determine the type of error that occurred
			if (theError.errorType() == DataAccessErrorType::SourceNotFound) {
				toast->setBody("Source not found: " + theError.errorMessage());
				toast->show();
			} else if (theError.errorType()
					== DataAccessErrorType::ConnectionFailure) {
				toast->setBody(
						"Connection failure: " + theError.errorMessage());
				toast->show();
			} else if (theError.errorType()
					== DataAccessErrorType::OperationFailure) {
				toast->setBody("Operation failure: " + theError.errorMessage());
				toast->show();
			}
		}
		//toast->setBody(list.toString());
		//toast->show();
		// Insert the data into the data model. Because the root of the .json file
		// is an array, a QVariant(QVariantList) is returned from load(). You can
		// provide a QVariantList to a data model directly by using insertList().
		usersModel->insertList(list.value<QVariantList>());

		// Set the data model for the list view
		mListView->setDataModel(usersModel);

		mActivityIndicator->stop();

	} else {
		toast->setBody("\n Problem with the network\n" + reply->errorString());
		toast->show();
	}
}

