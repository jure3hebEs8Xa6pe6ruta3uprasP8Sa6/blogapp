#include <QtCore>
#include <TreeFrogView>
#include "blogapp.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blogapp_createView : public TActionView
{
  Q_OBJECT
public:
  blogapp_createView() : TActionView() { }
  QString toString();
};

QString blogapp_createView::toString()
{
  responsebody.reserve(1234);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, blogapp);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>New Blogapp</h1>\n\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>Title<br /><input name=\"blogapp[title]\" value=\"");
  responsebody += THttpUtility::htmlEscape(blogapp["title"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Body<br /><input name=\"blogapp[body]\" value=\"");
  responsebody += THttpUtility::htmlEscape(blogapp["body"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Create\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(blogapp_createView)

#include "blogapp_createView.moc"
