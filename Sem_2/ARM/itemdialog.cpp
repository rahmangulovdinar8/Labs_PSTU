#include "itemdialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

ItemDialog::ItemDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Добавить предмет для обмена");
    setMinimumWidth(400);

    // --- Создаём виджеты ---
    nameEdit        = new QLineEdit(this);
    nameEdit->setPlaceholderText("напр. Учебник по физике");

    descriptionEdit = new QPlainTextEdit(this);
    descriptionEdit->setPlaceholderText("Краткое описание состояния предмета");
    descriptionEdit->setMaximumHeight(70);

    ownerEdit       = new QLineEdit(this);
    ownerEdit->setPlaceholderText("Фамилия Имя");

    roomEdit        = new QLineEdit(this);
    roomEdit->setPlaceholderText("напр. 314");

    categoryCombo   = new QComboBox(this);
    categoryCombo->addItems({
        "Электроника",   // 0
        "Книги",         // 1
        "Одежда",        // 2
        "Еда",           // 3
        "Гигиена",       // 4
        "Спорт/Игры",    // 5
        "Канцелярия",    // 6
        "Быт/Мебель",    // 7
        "Прочее"         // 8
    });

    wantEdit        = new QLineEdit(this);
    wantEdit->setPlaceholderText("что вас интересует взамен");

    buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // --- Форма ---
    QGroupBox   *group  = new QGroupBox("Информация о предмете", this);
    QFormLayout *form   = new QFormLayout(group);
    form->addRow("Название *",  nameEdit);
    form->addRow("Описание",    descriptionEdit);
    form->addRow("Ваше имя *",  ownerEdit);
    form->addRow("Комната *",   roomEdit);
    form->addRow("Категория",   categoryCombo);
    form->addRow("Хочу взамен", wantEdit);

    // --- Основной layout ---
    QVBoxLayout *main = new QVBoxLayout(this);
    main->addWidget(group);
    main->addWidget(buttonBox);

    // --- Сигналы ---
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ItemDialog::onAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void ItemDialog::onAccepted() {
    if (nameEdit->text().trimmed().isEmpty() ||
        ownerEdit->text().trimmed().isEmpty() ||
        roomEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Заполните обязательные поля (*)");
        return;
    }
    accept();
}

Item ItemDialog::getItem() const {
    Item item;
    item.id           = m_editId;
    item.name         = nameEdit->text().trimmed();
    item.description  = descriptionEdit->toPlainText().trimmed();
    item.ownerName    = ownerEdit->text().trimmed();
    item.ownerRoom    = roomEdit->text().trimmed();
    item.wantInReturn = wantEdit->text().trimmed();
    item.status       = ItemStatus::Available;
    item.addedAt      = QDateTime::currentDateTime();

    switch (categoryCombo->currentIndex()) {
    case 0: item.category = ItemCategory::Electronics; break;
    case 1: item.category = ItemCategory::Books;       break;
    case 2: item.category = ItemCategory::Clothing;    break;
    case 3: item.category = ItemCategory::Food;        break;
    case 4: item.category = ItemCategory::Hygiene;     break;
    case 5: item.category = ItemCategory::SportGame;   break;
    case 6: item.category = ItemCategory::Stationery;  break;
    case 7: item.category = ItemCategory::Furniture;   break;
    default: item.category = ItemCategory::Other;      break;
    }
    return item;
}

void ItemDialog::setItem(const Item &item) {
    m_editId = item.id;
    nameEdit->setText(item.name);
    descriptionEdit->setPlainText(item.description);
    ownerEdit->setText(item.ownerName);
    roomEdit->setText(item.ownerRoom);
    wantEdit->setText(item.wantInReturn);

    switch (item.category) {
    case ItemCategory::Electronics: categoryCombo->setCurrentIndex(0); break;
    case ItemCategory::Books:       categoryCombo->setCurrentIndex(1); break;
    case ItemCategory::Clothing:    categoryCombo->setCurrentIndex(2); break;
    case ItemCategory::Food:        categoryCombo->setCurrentIndex(3); break;
    case ItemCategory::Hygiene:     categoryCombo->setCurrentIndex(4); break;
    case ItemCategory::SportGame:   categoryCombo->setCurrentIndex(5); break;
    case ItemCategory::Stationery:  categoryCombo->setCurrentIndex(6); break;
    case ItemCategory::Furniture:   categoryCombo->setCurrentIndex(7); break;
    default:                        categoryCombo->setCurrentIndex(8); break;
    }
}
