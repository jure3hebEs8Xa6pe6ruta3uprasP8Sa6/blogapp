#include <QtCore>
#include <TreeFrogView>
#include "blogapp.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blogapp_loadView : public TActionView
{
  Q_OBJECT
public:
  blogapp_loadView() : TActionView() { }
  QString toString();
};

QString blogapp_loadView::toString()
{
  responsebody.reserve(921);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, blogapp);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Load Blogapp</h1>\n\n");
  responsebody += QVariant(formTag(urla("load"), Tf::Post, true)).toString();
  responsebody += QLatin1String("\n  <p>\n    File: <input name=\"csv\" type=\"file\">\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Upload\">\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(blogapp_loadView)

#include "blogapp_loadView.moc"
