#include <QtCore>
#include <TreeFrogView>
#include "blogapp.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blogapp_saveView : public TActionView
{
  Q_OBJECT
public:
  blogapp_saveView() : TActionView() { }
  QString toString();
};

QString blogapp_saveView::toString()
{
  responsebody.reserve(1617);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, blogapp);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Blogapp</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", blogapp["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"blogapp[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(blogapp["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>Title<br /><input type=\"text\" name=\"blogapp[title]\" value=\"");
  responsebody += THttpUtility::htmlEscape(blogapp["title"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Body<br /><input type=\"text\" name=\"blogapp[body]\" value=\"");
  responsebody += THttpUtility::htmlEscape(blogapp["body"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", blogapp["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(blogapp_saveView)

#include "blogapp_saveView.moc"
