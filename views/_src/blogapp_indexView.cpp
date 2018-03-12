#include <QtCore>
#include <TreeFrogView>
#include "blogapp.h" 
#include "applicationhelper.h"

class T_VIEW_EXPORT blogapp_indexView : public TActionView
{
  Q_OBJECT
public:
  blogapp_indexView() : TActionView() { }
  QString toString();
};

QString blogapp_indexView::toString()
{
  responsebody.reserve(1741);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n\n<h1>Listing Blogapp</h1>\n\n");
  responsebody += QVariant(linkTo("Create a new Blogapp", urla("create"))).toString();
  responsebody += QLatin1String("<br />\n");
  responsebody += QVariant(linkTo("Load CSV into Blogapp", urla("load"))).toString();
  responsebody += QLatin1String("<br />\n<br />\n<table border=\"1\" cellpadding=\"5\" style=\"border: 1px #d0d0d0 solid; border-collapse: collapse;\">\n  <tr>\n    <th>ID</th>\n    <th>Title</th>\n    <th>Body</th>\n  </tr>\n");
  tfetch(QList<Blogapp>, blogappList);
  for (const auto &i : blogappList) {
  responsebody += QLatin1String("  <tr>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.id());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.title());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.body());
  responsebody += QLatin1String("</td>\n    <td>\n      ");
  responsebody += QVariant(linkTo("Show", urla("show", i.id()))).toString();
  responsebody += QLatin1String("\n      ");
  responsebody += QVariant(linkTo("Edit", urla("save", i.id()))).toString();
  responsebody += QLatin1String("\n      ");
  responsebody += QVariant(linkTo("Remove", urla("remove", i.id()), Tf::Post, "confirm('Are you sure?')")).toString();
  responsebody += QLatin1String("\n    </td>\n  </tr>\n");
  };
  responsebody += QLatin1String("</table>\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(blogapp_indexView)

#include "blogapp_indexView.moc"
