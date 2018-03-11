#ifndef BLOGAPPCONTROLLER_H
#define BLOGAPPCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT BlogappController : public ApplicationController
{
    Q_OBJECT
public:
    BlogappController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // BLOGAPPCONTROLLER_H
