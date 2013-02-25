// Default empty project template
#ifndef PointClient_HPP_
#define PointClient_HPP_

#include <QObject>
#include <QFile>

#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ListView>
using namespace bb::cascades;

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 * Use this object to create and init app UI, to create context objects,
 * to register the new meta types etc.
 */
class PointClient : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructor.
     */
    PointClient(bb::cascades::Application *app);
    /*!
     * Initiates the network request.
     */
    Q_INVOKABLE void initiateRequest();

private slots:
    /*!
     * Handles the network reply.
     */
    void requestFinished(QNetworkReply* reply);

private:
    ActivityIndicator *mActivityIndicator;
    ListView *mListView;
    QNetworkAccessManager *mNetworkAccessManager;
    QFile *mFile;
};



#endif /* PointClient_HPP_ */
