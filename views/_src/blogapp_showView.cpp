#include <QtCore>
#include <TreeFrogView>
#include "blogapp.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blogapp_showView : public TActionView
{
  Q_OBJECT
public:
  blogapp_showView() : TActionView() { }
  QString toString();
};

QString blogapp_showView::toString()
{
  responsebody.reserve(1593);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(Blogapp, blogapp);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Blogapp</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Title</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.title());
  responsebody += QLatin1String("</dd><br />\n<dt>Body</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.body());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Lock Revision</dt><dd>");
  responsebody += THttpUtility::htmlEscape(blogapp.lockRevision());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", blogapp.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(blogapp_showView)

#include "blogapp_showView.moc"
