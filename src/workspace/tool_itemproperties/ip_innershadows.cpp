#include "ip_innershadows.h"
#include "ui_ip_shadows.h"

ipInnerShadows::ipInnerShadows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ipShadows)
{
    ui->setupUi(this);

    unloadItems();
}

ipInnerShadows::~ipInnerShadows()
{
    delete ui;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ipInnerShadows::setActiveItem(AbstractItemBase *item)
{    
    ItemBase *activeItem = dynamic_cast<ItemBase*>(item);

    if(activeItem){
        if(activeItem != m_item){
            m_item = activeItem;
            loadProperties();
        }
    }else{
        unloadItems();
    }

}

/***************************************************
 *
 * Members
 *
 ***************************************************/

void ipInnerShadows::loadProperties()
{

    this->setEnabled(true);
    emit sendCollapse(false);

    resetItems();

    switch(m_item->itemType()){
    case ItemType::Oval:
    case ItemType::Polygon:
    case ItemType::Rect:
    case ItemType::Star:
    case ItemType::Triangle:
        loadShadows();
        break;
    case ItemType::Instance:
    case ItemType::Line:
    case ItemType::Text:
    default:
        resetItems();
        break;
    }
}


void ipInnerShadows::resetItems()
{

    m_propertyItemList = new QList<PropertyShadow*>();

    QList<QWidget *> widgets = findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        widget->deleteLater();
    }
}

void ipInnerShadows::unloadItems()
{
    this->setEnabled(false);
    emit sendCollapse(true);

    m_item = nullptr;
    resetItems();
}

void ipInnerShadows::loadShadows()
{
    foreach(Shadow m_property, m_item->innerShadowList()){
        PropertyShadow * pf = new PropertyShadow();
        pf->setShadow(m_property);
        addShadow(pf);
    }
}

void ipInnerShadows::addShadow(PropertyShadow *propertyItem)
{
    connect(propertyItem, &PropertyShadow::hasChanged, this, &ipInnerShadows::updateItem);

    m_propertyItemList->append(propertyItem);
    ui->layout->addWidget(propertyItem);
}

void ipInnerShadows::removeShadow(PropertyShadow *propertyItem)
{
    disconnect(propertyItem, &PropertyShadow::hasChanged, this, &ipInnerShadows::updateItem);

    m_propertyItemList->removeOne(propertyItem);
    ui->layout->removeWidget(propertyItem);
}

void ipInnerShadows::newShadow()
{
    if(!m_item) return;

    Shadow m_newProperty;
    PropertyShadow * m_newPropertyItem = new PropertyShadow(m_newProperty);

    m_item->addInnerShadow(m_newProperty);
    m_item->update();
    addShadow(m_newPropertyItem);
}

void ipInnerShadows::updateItem()
{
    PropertyShadow * m_changedProperty = dynamic_cast<PropertyShadow*>(sender());

    if(m_changedProperty && m_item){

       m_item->updateInnerShadow(m_changedProperty->shadow());

    }
}