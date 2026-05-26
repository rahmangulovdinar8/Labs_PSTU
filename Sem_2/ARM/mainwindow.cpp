#include "mainwindow.h"
#include "itemdialog.h"
#include "chaindialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QSplitter>
#include <QGroupBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_model(new BarterModel(this))
    , m_tradeManager(new TradeManager(m_model, this))
{
    setWindowTitle("🏠 Бартерный Обмен в Общежитии");
    resize(1050, 680);

    buildUI();


    tableView->setModel(m_model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet(
        "QTableView { font-size: 12px; }"
        "QHeaderView::section { background-color: #34495e; color: white;"
        " padding: 4px; font-weight: bold; }");


    connect(addButton,    &QPushButton::clicked, this, &MainWindow::onAddItem);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItem);
    connect(tradeButton,  &QPushButton::clicked, this, &MainWindow::onMakeTrade);
    connect(chainButton,  &QPushButton::clicked, this, &MainWindow::onFindChains);

    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onItemSelectionChanged);

    connect(m_model, &BarterModel::dataChanged2, this, &MainWindow::refreshGL);
    connect(m_tradeManager, &TradeManager::tradeCompleted,
            this, &MainWindow::onTradeCompleted);

    // ── Загружаем данные из файла ──
    QVector<Item> savedItems;
    QVector<TradeRecord> savedHistory;
    if (Storage::load(savedItems, savedHistory)) {
        m_model->loadItems(savedItems);
        // Восстанавливаем историю обменов в TradeManager
        m_tradeManager->loadHistory(savedHistory);
        // Показываем историю в списке
        for (int i = savedHistory.size() - 1; i >= 0; --i) {
            const TradeRecord &rec = savedHistory[i];
            historyList->addItem(
                QString("[%1] %2 ↔ %3")
                .arg(rec.tradedAt.toString("dd.MM hh:mm"),
                     rec.personA, rec.personB));
        }
        statusLabel->setText(QString("Загружено: %1 предметов, %2 обменов")
                             .arg(savedItems.size()).arg(savedHistory.size()));
    } else {
        // Первый запуск — добавляем примеры
        auto addExample = [&](const QString &name, const QString &desc,
                               const QString &owner, const QString &room,
                               ItemCategory cat, const QString &want) {
            Item it;
            it.id = m_model->nextId();
            it.name = name; it.description = desc;
            it.ownerName = owner; it.ownerRoom = room;
            it.category = cat; it.status = ItemStatus::Available;
            it.wantInReturn = want;
            it.addedAt = QDateTime::currentDateTime();
            m_model->addItem(it);
        };
        addExample("Учебник по Физике", "Савельев том 1-2",
                   "Иванов Петр", "214", ItemCategory::Books, "Учебник Математика");
        addExample("Наушники Sony", "Беспроводные, USB-C",
                   "Смирнова Анна", "308", ItemCategory::Electronics, "Клавиатура");
        addExample("Зимняя куртка M", "Синяя, почти новая",
                   "Козлов Дмитрий", "112", ItemCategory::Clothing, "Куртка L");
        statusLabel->setText("Первый запуск — добавлены примеры");
    }

    refreshGL();
    updateStats();
}

MainWindow::~MainWindow() {}

void MainWindow::buildUI() {
    // ── Заголовок ──
    QLabel *title = new QLabel("🔄 Система Бартерного Обмена — Общежитие", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:16px; font-weight:bold; color:#2c3e50;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #dfe6e9,stop:1 #b2bec3);"
        "padding:8px; border-radius:4px;");

    // ── Кнопки ──
    addButton = new QPushButton("➕ Добавить предмет", this);
    addButton->setStyleSheet(
        "QPushButton{background:#27ae60;color:white;font-weight:bold;"
        "padding:8px 16px;border-radius:4px;}"
        "QPushButton:hover{background:#2ecc71;}");

    removeButton = new QPushButton("🗑 Удалить", this);
    removeButton->setStyleSheet(
        "QPushButton{background:#e74c3c;color:white;font-weight:bold;"
        "padding:8px 16px;border-radius:4px;}"
        "QPushButton:hover{background:#c0392b;}");

    tradeButton = new QPushButton("🤝 Оформить обмен", this);
    tradeButton->setEnabled(false);
    tradeButton->setStyleSheet(
        "QPushButton{background:#2980b9;color:white;font-weight:bold;"
        "padding:8px 16px;border-radius:4px;}"
        "QPushButton:hover{background:#3498db;}"
        "QPushButton:disabled{background:#95a5a6;}");

    chainButton = new QPushButton("🔗 Найти цепочки", this);
    chainButton->setStyleSheet(
        "QPushButton{background:#8e44ad;color:white;font-weight:bold;"
        "padding:8px 16px;border-radius:4px;}"
        "QPushButton:hover{background:#9b59b6;}");

    statsLabel = new QLabel("Предметов: 0 | Обменов: 0", this);
    statsLabel->setStyleSheet("font-size:12px;color:#555;padding:4px;");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(addButton);
    btnLayout->addWidget(removeButton);
    btnLayout->addWidget(tradeButton);
    btnLayout->addWidget(chainButton);
    btnLayout->addStretch();
    btnLayout->addWidget(statsLabel);

    // ── Таблица + детали (левая часть) ──
    tableView   = new QTableView(this);
    detailsText = new QTextEdit(this);
    detailsText->setReadOnly(true);
    detailsText->setMaximumHeight(120);
    detailsText->setStyleSheet("font-size:11px;background:#f8f9fa;");

    QGroupBox *detailsGroup = new QGroupBox("Детали выбранного предмета", this);
    QVBoxLayout *detailsLay = new QVBoxLayout(detailsGroup);
    detailsLay->addWidget(detailsText);

    QWidget     *leftWidget = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(0,0,0,0);
    leftLayout->addWidget(tableView);
    leftLayout->addWidget(detailsGroup);

    // ── OpenGL + История (правая часть) ──
    glWidget = new GLWidget(this);
    glWidget->setMinimumHeight(260);

    QGroupBox   *glGroup  = new QGroupBox("📊 Визуализация (OpenGL)", this);
    QVBoxLayout *glLayout = new QVBoxLayout(glGroup);
    glLayout->addWidget(glWidget);

    historyList = new QListWidget(this);
    historyList->setStyleSheet("font-size:11px;");

    QGroupBox   *histGroup  = new QGroupBox("📋 История обменов", this);
    QVBoxLayout *histLayout = new QVBoxLayout(histGroup);
    histLayout->addWidget(historyList);

    QWidget     *rightWidget = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->addWidget(glGroup, 3);
    rightLayout->addWidget(histGroup, 2);

    // ── Сплиттер ──
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 2);

    // ── Центральный виджет ──
    QWidget     *central    = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(title);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(splitter);
    setCentralWidget(central);

    // ── Меню ──
    QMenu   *fileMenu  = menuBar()->addMenu("Файл");
    QAction *exitAct   = fileMenu->addAction("Выход");
    connect(exitAct, &QAction::triggered, this, &QMainWindow::close);

    QMenu   *helpMenu  = menuBar()->addMenu("Справка");
    QAction *aboutAct  = helpMenu->addAction("О программе");
    connect(aboutAct, &QAction::triggered, this, [this](){
        QMessageBox::about(this, "О программе",
            "<h3>Бартерный Обмен в Общежитии</h3>"
            "<p>АРМ специалиста по учёту бартерных сделок.</p>"
            "<p>Стек: Qt 5 Widgets + OpenGL</p>"
            "<ul><li>Добавление предметов для обмена</li>"
            "<li>Оформление сделок между жильцами</li>"
            "<li>OpenGL-диаграмма по категориям</li>"
            "<li>История всех обменов</li></ul>");
    });

    // ── Статус-бар ──
    statusLabel = new QLabel("Готово", this);
    statusBar()->addWidget(statusLabel);
}

void MainWindow::onAddItem() {
    ItemDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Item item = dlg.getItem();
        item.id   = m_model->nextId();
        m_model->addItem(item);
        updateStats();
        statusLabel->setText(QString("Добавлен: %1").arg(item.name));
        saveData();
    }
}

void MainWindow::onRemoveItem() {
    QModelIndexList sel = tableView->selectionModel()->selectedRows();
    if (sel.isEmpty()) {
        QMessageBox::information(this, "Удаление", "Выберите строку для удаления.");
        return;
    }
    int row = sel.first().row();
    Item *it = m_model->getItem(row);
    if (!it) return;

    if (QMessageBox::question(this, "Удаление",
            QString("Удалить \"%1\"?").arg(it->name)) == QMessageBox::Yes) {
        m_model->removeItem(row);
        detailsText->clear();
        updateStats();
        statusLabel->setText("Предмет удалён.");
        saveData();
    }
}

void MainWindow::onMakeTrade() {
    QModelIndexList sel = tableView->selectionModel()->selectedRows();
    if (sel.size() < 2) {
        QMessageBox::information(this, "Обмен",
            "Выберите ровно 2 предмета (Ctrl+клик), затем нажмите кнопку.");
        return;
    }
    Item *a = m_model->getItem(sel[0].row());
    Item *b = m_model->getItem(sel[1].row());
    if (!a || !b) return;

    if (a->status != ItemStatus::Available || b->status != ItemStatus::Available) {
        QMessageBox::warning(this, "Обмен",
            "Оба предмета должны иметь статус «Доступен».");
        return;
    }
    if (QMessageBox::question(this, "Подтвердить обмен",
            QString("Обменять:\n«%1» (%2)\n↔\n«%3» (%4)?")
            .arg(a->name, a->ownerName, b->name, b->ownerName))
            == QMessageBox::Yes)
    {
        if (m_tradeManager->makeTrade(a->id, b->id)) {
            QMessageBox::information(this, "Успех", "Обмен оформлен!");
            updateStats();
            saveData();
        }
    }
}

void MainWindow::onItemSelectionChanged() {
    QModelIndexList sel = tableView->selectionModel()->selectedRows();
    tradeButton->setEnabled(sel.size() == 2);

    if (sel.isEmpty()) { detailsText->clear(); return; }

    Item *it = m_model->getItem(sel.last().row());
    if (!it) return;

    detailsText->setHtml(QString(
        "<b>Название:</b> %1<br>"
        "<b>Описание:</b> %2<br>"
        "<b>Владелец:</b> %3, комната <b>%4</b><br>"
        "<b>Категория:</b> %5 &nbsp; <b>Статус:</b> %6<br>"
        "<b>Хочет взамен:</b> %7<br>"
        "<b>Добавлен:</b> %8")
        .arg(it->name, it->description.isEmpty() ? "—" : it->description,
             it->ownerName, it->ownerRoom,
             Item::categoryName(it->category), Item::statusName(it->status),
             it->wantInReturn.isEmpty() ? "не указано" : it->wantInReturn,
             it->addedAt.toString("dd.MM.yyyy hh:mm")));
}

void MainWindow::onTradeCompleted(TradeRecord record) {
    historyList->insertItem(0,
        QString("[%1] %2 ↔ %3")
        .arg(record.tradedAt.toString("hh:mm"), record.personA, record.personB));
    statusLabel->setText(QString("Обмен #%1 оформлен!").arg(record.id));
}

void MainWindow::refreshGL() {
    glWidget->setData(m_model->categoryCounts(), m_model->items().size());
}

void MainWindow::updateStats() {
    int avail = 0;
    for (const Item &it : m_model->items())
        if (it.status == ItemStatus::Available) ++avail;
    statsLabel->setText(
        QString("Предметов: %1 (доступно: %2) | Обменов: %3")
        .arg(m_model->items().size()).arg(avail)
        .arg(m_tradeManager->history().size()));
}

void MainWindow::onFindChains() {
    ChainFinder finder(m_model->items());
    QVector<BarterChain> chains = finder.findChains(5);

    ChainDialog dlg(chains, this);
    if (dlg.exec() == QDialog::Accepted) {
        int idx = dlg.selectedChainIndex();
        if (idx < 0 || idx >= chains.size()) return;

        const BarterChain &chain = chains[idx];
        int success = 0;
        for (const ChainStep &step : chain.steps) {
            if (m_tradeManager->makeTrade(step.giverId, step.takerId))
                ++success;
        }

        QMessageBox::information(this, "Цепочка оформлена",
            QString("Успешно оформлено обменов: %1 из %2")
            .arg(success).arg(chain.length()));

        updateStats();
        refreshGL();
        saveData(); // сохраняем после цепочки
    }
}

void MainWindow::saveData() {
    if (Storage::save(m_model->items(), m_tradeManager->history())) {
        statusLabel->setText("💾 Сохранено: " +
            QDateTime::currentDateTime().toString("hh:mm:ss"));
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveData();
    event->accept();
}
