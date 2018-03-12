#ifndef BLOGAPP_H
#define BLOGAPP_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class BlogappObject;
class QJsonArray;


class T_MODEL_EXPORT Blogapp : public TAbstractModel
{
public:
    Blogapp();
    Blogapp(const Blogapp &other);
    Blogapp(const BlogappObject &object);
    ~Blogapp();

    int id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString body() const;
    void setBody(const QString &body);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Blogapp &operator=(const Blogapp &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static bool load(const QString &filename);
    static Blogapp create(const QString &title, const QString &body);
    static Blogapp create(const QVariantMap &values);
    static Blogapp get(int id);
    static Blogapp get(int id, int lockRevision);
    static int count();
    static QList<Blogapp> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<BlogappObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Blogapp &model);
    friend QDataStream &operator>>(QDataStream &ds, Blogapp &model);
};

Q_DECLARE_METATYPE(Blogapp)
Q_DECLARE_METATYPE(QList<Blogapp>)

#endif // BLOGAPP_H
