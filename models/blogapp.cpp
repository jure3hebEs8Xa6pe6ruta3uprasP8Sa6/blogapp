#include <TreeFrogModel>
#include "blogapp.h"
#include "blogappobject.h"

#include <QDir>
#include <QFile>
#include <QTime>
#include <QList>
#include <QTextCodec>
#include <QDebug>

#include "qtcsv/reader.h"
#include "qtcsv/stringdata.h"
#include "qtcsv/variantdata.h"

Blogapp::Blogapp()
        : TAbstractModel(), d(new BlogappObject()) {
    d->id = 0;
    d->lock_revision = 0;
}

Blogapp::Blogapp(const Blogapp &other)
        : TAbstractModel(), d(new BlogappObject(*other.d)) {}

Blogapp::Blogapp(const BlogappObject &object)
        : TAbstractModel(), d(new BlogappObject(object)) {}

Blogapp::~Blogapp() {
    // If the reference count becomes 0,
    // the shared data object 'BlogappObject' is deleted.
}

int Blogapp::id() const {
    return d->id;
}

QString Blogapp::title() const {
    return d->title;
}

void Blogapp::setTitle(const QString &title) {
    d->title = title;
}

QString Blogapp::body() const {
    return d->body;
}

void Blogapp::setBody(const QString &body) {
    d->body = body;
}

QDateTime Blogapp::createdAt() const {
    return d->created_at;
}

QDateTime Blogapp::updatedAt() const {
    return d->updated_at;
}

int Blogapp::lockRevision() const {
    return d->lock_revision;
}

Blogapp &Blogapp::operator=(const Blogapp &other) {
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Blogapp::load(const QString &filename) {
    tDebug("Model qtcsv Blogapp::load");
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QList<QStringList> readData = QtCSV::Reader::readToList(filename);

//    for (int i = 0; i < readData.size(); ++i) {
//        qDebug() << readData.at(i).join(",");
//    }


    //tDebug("New Values: %s %s", title.c_str(), body.c_str());
    return true;
}

Blogapp Blogapp::create(const QString &title, const QString &body) {
    BlogappObject obj;
    obj.title = title;
    obj.body = body;
    if (!obj.create()) {
        return Blogapp();
    }
    return Blogapp(obj);
}

Blogapp Blogapp::create(const QVariantMap &values) {
    Blogapp model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Blogapp Blogapp::get(int id) {
    TSqlORMapper<BlogappObject> mapper;
    return Blogapp(mapper.findByPrimaryKey(id));
}

Blogapp Blogapp::get(int id, int lockRevision) {
    TSqlORMapper<BlogappObject> mapper;
    TCriteria cri;
    cri.add(BlogappObject::Id, id);
    cri.add(BlogappObject::LockRevision, lockRevision);
    return Blogapp(mapper.findFirst(cri));
}

int Blogapp::count() {
    TSqlORMapper<BlogappObject> mapper;
    return mapper.findCount();
}

QList<Blogapp> Blogapp::getAll() {
    return tfGetModelListByCriteria<Blogapp, BlogappObject>(TCriteria());
}

QJsonArray Blogapp::getAllJson() {
    QJsonArray array;
    TSqlORMapper<BlogappObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<BlogappObject> i(mapper); i.hasNext();) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Blogapp(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Blogapp::modelData() {
    return d.data();
}

const TModelObject *Blogapp::modelData() const {
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Blogapp &model) {
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Blogapp &model) {
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Blogapp)
