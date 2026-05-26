#include "chaindialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTabWidget>
#include <QMessageBox>

ChainDialog::ChainDialog(const QVector<BarterChain> &chains, QWidget *parent)
    : QDialog(parent), m_chains(chains)
{
    setWindowTitle("🔗 Найденные цепочки обмена");
    setMinimumSize(750, 520);

    // ── Заголовок ──
    QLabel *header = new QLabel(this);
    if (chains.isEmpty()) {
        header->setText("❌ Цепочки не найдены. Заполните поле «Хочу взамен» у предметов.");
        header->setStyleSheet("color:#e74c3c;font-size:13px;padding:8px;"
                              "background:#2c1010;border-radius:4px;");
    } else {
        header->setText(QString("✅ Найдено цепочек: %1  —  выберите одну для просмотра и оформления")
                        .arg(chains.size()));
        header->setStyleSheet("color:#2ecc71;font-size:13px;font-weight:bold;"
                              "padding:8px;background:#102c10;border-radius:4px;");
    }

    // ── Список цепочек слева ──
    m_listWidget = new QListWidget(this);
    m_listWidget->setMaximumWidth(220);
    m_listWidget->setStyleSheet(
        "QListWidget{font-size:12px;background:#1a1a2e;color:#eee;border:none;}"
        "QListWidget::item{padding:6px;border-bottom:1px solid #333;}"
        "QListWidget::item:selected{background:#2980b9;color:white;}");

    for (int i = 0; i < chains.size(); ++i) {
        const BarterChain &c = chains[i];
        QString participants;
        for (const ChainStep &s : c.steps)
            participants += s.giverName.split(" ").first() + "→";
        if (!participants.isEmpty())
            participants.chop(1); // убрать последний →
        m_listWidget->addItem(
            QString("#%1  [%2 чел.]\n%3").arg(i+1).arg(c.length()).arg(participants));
    }

    // ── Вкладки: детали + граф ──
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setStyleSheet(
        "QTabWidget::pane{border:1px solid #333;background:#12121e;}"
        "QTabBar::tab{background:#1a1a2e;color:#aaa;padding:6px 16px;}"
        "QTabBar::tab:selected{background:#2980b9;color:white;}");

    // Вкладка 1 — Детали текстом
    m_detailText = new QTextEdit(this);
    m_detailText->setReadOnly(true);
    m_detailText->setStyleSheet("background:#12121e;color:#ddd;font-size:12px;border:none;");
    m_detailText->setPlaceholderText("Выберите цепочку слева...");
    tabs->addTab(m_detailText, "📋 Детали");

    // Вкладка 2 — Визуализация графа
    m_graphWidget = new GraphWidget(this);
    if (!chains.isEmpty())
        m_graphWidget->setChains(chains);
    tabs->addTab(m_graphWidget, "🕸 Граф обменов");

    // ── Сплиттер: список | вкладки ──
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(m_listWidget);
    splitter->addWidget(tabs);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    // ── Кнопки ──
    m_confirmBtn = new QPushButton("✅ Оформить выбранную цепочку", this);
    m_confirmBtn->setEnabled(false);
    m_confirmBtn->setStyleSheet(
        "QPushButton{background:#27ae60;color:white;font-weight:bold;"
        "padding:8px 20px;border-radius:4px;}"
        "QPushButton:disabled{background:#2c3e50;color:#666;}"
        "QPushButton:hover{background:#2ecc71;}");

    QPushButton *closeBtn = new QPushButton("Закрыть", this);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2c3e50;color:#ccc;padding:8px 20px;border-radius:4px;}"
        "QPushButton:hover{background:#34495e;}");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(m_confirmBtn);
    btnLayout->addWidget(closeBtn);

    // ── Основной layout ──
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setSpacing(8);
    main->addWidget(header);
    main->addWidget(splitter, 1);
    main->addLayout(btnLayout);

    // Тёмный фон диалога
    setStyleSheet("QDialog{background:#0f0f1a;}");

    connect(m_listWidget, &QListWidget::currentRowChanged,
            this, &ChainDialog::onChainSelected);
    connect(m_confirmBtn, &QPushButton::clicked, this, &ChainDialog::onConfirm);
    connect(closeBtn,     &QPushButton::clicked, this, &QDialog::reject);

    // Выбрать первую цепочку автоматически
    if (!chains.isEmpty())
        m_listWidget->setCurrentRow(0);
}

void ChainDialog::onChainSelected(int row) {
    if (row < 0 || row >= m_chains.size()) return;
    m_selectedIndex = row;
    m_confirmBtn->setEnabled(true);

    const BarterChain &c = m_chains[row];

    // ── Текстовые детали ──
    QString html = QString(
        "<div style='font-family:Arial;color:#ddd;'>"
        "<h3 style='color:#3498db;'>Цепочка #%1</h3>"
        "<p><b style='color:#aaa'>Участников:</b> <b style='color:#2ecc71'>%2</b></p>"
        "<hr style='border-color:#333;'>"
        "<table width='100%%' cellspacing='0' cellpadding='6'>")
        .arg(row + 1).arg(c.length());

    html += "<tr style='background:#1e2a3a;'>"
            "<th align='left' style='color:#3498db'>Кто отдаёт</th>"
            "<th align='left' style='color:#e67e22'>Предмет</th>"
            "<th align='left' style='color:#2ecc71'>Кто получает</th></tr>";

    for (int i = 0; i < c.steps.size(); ++i) {
        const ChainStep &s = c.steps[i];
        QString bg = (i % 2 == 0) ? "#151525" : "#1a1a2e";
        html += QString("<tr style='background:%1;'>"
                        "<td><b>%2</b></td>"
                        "<td>🔄 <i>%3</i></td>"
                        "<td><b>%4</b></td></tr>")
                .arg(bg, s.giverName, s.itemName, s.takerName);
    }
    html += "</table><hr style='border-color:#333;'>"
            "<p style='color:#7f8c8d;font-size:11px;'>"
            "После оформления все предметы получат статус «Обменян»</p></div>";

    m_detailText->setHtml(html);

    // ── Подсветить цепочку на графе ──
    m_graphWidget->highlightChain(row);
}

void ChainDialog::onConfirm() {
    if (m_selectedIndex < 0) return;
    const BarterChain &c = m_chains[m_selectedIndex];

    QString msg = QString("Оформить цепочку из %1 обменов?\n\n").arg(c.length());
    for (const ChainStep &s : c.steps)
        msg += QString("• %1  →  «%2»  →  %3\n")
               .arg(s.giverName, s.itemName, s.takerName);

    if (QMessageBox::question(this, "Подтверждение", msg) == QMessageBox::Yes)
        accept();
}
