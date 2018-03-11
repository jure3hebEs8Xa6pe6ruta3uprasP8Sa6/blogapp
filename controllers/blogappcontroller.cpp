#include "blogappcontroller.h"
#include "blogapp.h"


void BlogappController::index()
{
    auto blogappList = Blogapp::getAll();
    texport(blogappList);
    render();
}

void BlogappController::show(const QString &id)
{
    auto blogapp = Blogapp::get(id.toInt());
    texport(blogapp);
    render();
}

void BlogappController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto blogapp = httpRequest().formItems("blogapp");
        auto model = Blogapp::create(blogapp);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(blogapp);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void BlogappController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Blogapp::get(id.toInt());
        if (!model.isNull()) {
            session().insert("blogapp_lockRevision", model.lockRevision());
            auto blogapp = model.toVariantMap();
            texport(blogapp);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        int rev = session().value("blogapp_lockRevision").toInt();
        auto model = Blogapp::get(id.toInt(), rev);
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto blogapp = httpRequest().formItems("blogapp");
        model.setProperties(blogapp);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(blogapp);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void BlogappController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto blogapp = Blogapp::get(id.toInt());
    blogapp.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(BlogappController)
