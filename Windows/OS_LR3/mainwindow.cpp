#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    GetSystemInfo(&structSys);

    ui->listWidget->addItem("Size page memory: " + QString::number(structSys.dwPageSize));

    ui->listWidget->addItem("Minimum application address: 0x" + QString::number(reinterpret_cast<int>(structSys.lpMinimumApplicationAddress), 16));

    ui->listWidget->addItem("Maximum application address: 0x" + QString::number(reinterpret_cast<int>(structSys.lpMaximumApplicationAddress), 16));

    ui->listWidget->addItem("Granularity of reservation of regions of address space: " + QString::number(structSys.dwAllocationGranularity));
}

void MainWindow::on_pushButton_2_clicked() {
    MEMORYSTATUS mem;
    mem.dwLength = sizeof(MEMORYSTATUS);
    GlobalMemoryStatus(&mem);
    ui->listWidget_2->addItem("Size struct: " + QString::number(mem.dwLength));
    ui->listWidget_2->addItem("Employment subsystem management memory: " + QString::number(mem.dwMemoryLoad));
    ui->listWidget_2->addItem("Volume physical memory: " + QString::number(mem.dwTotalPhys));
    ui->listWidget_2->addItem("Volume free physical memory: " + QString::number(mem.dwAvailPhys));
    ui->listWidget_2->addItem("Max byte in page file: " + QString::number(mem.dwTotalPageFile));
    ui->listWidget_2->addItem("Free byte in page file: " + QString::number(mem.dwAvailPageFile));
    ui->listWidget_2->addItem("Volume memory for closed memory space: " + QString::number(mem.dwTotalVirtual));
    ui->listWidget_2->addItem("Free memory space: " + QString::number(mem.dwAvailVirtual));
    ui->listWidget_2->addItem("");
}

void MainWindow::on_pushButton_3_clicked() {
    if (ui->listWidget->count() > 0) {
        ui->listWidget->clear();
    }
    if (ui->listWidget_2->count() > 0) {
        ui->listWidget_2->clear();
    }
    if (ui->listWidget_3->count() > 0) {
        ui->listWidget_3->clear();
    }
    if (ui->listWidget_4->count() > 0) {
        ui->listWidget_4->clear();
    }
    if (ui->listWidget_5->count() > 0) {
        ui->listWidget_5->clear();
    }
    ui->lineEdit_4->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

QString Type(DWORD t) {
    QString str;

    switch (t) {
        case 0x1000000: {
            str = "IMAGE";
            break;
        }
        case 0x40000: {
            str = "MAPPED";
            break;
        }
        case 0x20000: {
            str = "PRIVATE";
            break;
        }
        default: {
            str = '-';
        }
    }
    return str;
}

QString State(DWORD t) {
    QString str;

    switch (t) {
        case 0x1000: {
            str = "COMMIT";
            break;
        }
        case 0x10000: {
            str = "FREE";
            break;
        }
        case 0x2000: {
            str = "RESERVE";
            break;
        }
        default: {
            str = '-';
        }
    }
    return str;
}

QString Protect(DWORD t) {
    QString str;

    switch (t) {
        case 0x10: {
            str = "EXECUTE";
            break;
        }
        case 0x20: {
            str = "EXECUTE_READ";
            break;
        }
        case 0x40: {
            str = "EXECUTE_READWRITE";
            break;
        }
        case 0x80: {
            str = "EXECUTE_WRITECOPY";
            break;
        }
        case 0x01: {
            str = "NOACCESS";
            break;
        }
        case 0x02: {
            str = "READONLY";
            break;
        }
        case 0x04: {
            str = "READWRITE";
            break;
        }
        case 0x08: {
            str = "WRITECOPY";
            break;
        }
        case 0x40000000: {
            str = "TARGETS_INVALID";
            break;
        }
        case 0x100: {
            str = "GUARD";
            break;
        }
        case 0x200: {
            str = "NOCACHE";
            break;
        }
        case 0x400: {
            str = "WRITECOMBINE";
            break;
        }
        default: {
            str = '-';
        }
    }
    return str;
}

void MainWindow::on_pushButton_4_clicked() {
    unsigned long i;
    for (i = reinterpret_cast<unsigned long>(structSys.lpMinimumApplicationAddress); i <= reinterpret_cast<unsigned long>(structSys.lpMaximumApplicationAddress); i += reinterpret_cast<unsigned long>(structSys.dwAllocationGranularity)) {

    //for (i = reinterpret_cast<unsigned long>(structSys.lpMinimumApplicationAddress); i <= reinterpret_cast<unsigned long>(structSys.lpMaximumApplicationAddress); i += reinterpret_cast<unsigned long>(pmbi.RegionSize)) {
        VirtualQuery(reinterpret_cast<LPVOID>(i), &pmbi, (DWORD)sizeof(pmbi));

        ui->listWidget_3->addItem("Type: " + Type(pmbi.Type));
        ui->listWidget_3->addItem("State: " + State(pmbi.State));
        ui->listWidget_3->addItem("Protect: " + QString::number(pmbi.Protect));
        ui->listWidget_3->addItem("RegionSize: " + QString::number(pmbi.RegionSize));
        ui->listWidget_3->addItem("BaseAddress: 0x" + QString::number(reinterpret_cast<int>(pmbi.BaseAddress), 16));
        ui->listWidget_3->addItem("AllocationBase: 0x" + QString::number(reinterpret_cast<int>(pmbi.AllocationBase), 16));
        ui->listWidget_3->addItem("AllocationProtect: " + Protect(pmbi.AllocationProtect));
        ui->listWidget_3->addItem("");
    }


}

void MainWindow::on_pushButton_5_clicked() {
    long i = ui->lineEdit_3->text().toLong(&ok, 16);

    VirtualQuery(reinterpret_cast<LPVOID>(i), &pmbi, (DWORD)sizeof(pmbi));

    ui->listWidget_5->addItem("Type: " + Type(pmbi.Type));
    ui->listWidget_5->addItem("State: " + State(pmbi.State));
    ui->listWidget_5->addItem("Protect: " + QString::number(pmbi.Protect));
    ui->listWidget_5->addItem("RegionSize: " + QString::number(pmbi.RegionSize));
    ui->listWidget_5->addItem("BaseAddress: 0x" + QString::number(reinterpret_cast<int>(pmbi.BaseAddress), 16));
    ui->listWidget_5->addItem("AllocationBase: 0x" + QString::number(reinterpret_cast<int>(pmbi.AllocationBase), 16));
    ui->listWidget_5->addItem("AllocationProtect: " + Protect(pmbi.AllocationProtect));
    ui->listWidget_5->addItem("");
}

void MainWindow::on_pushButton_6_clicked() {
    QString size = ui->lineEdit_2->text();
    PVOID i;
    if (ui->lineEdit->text() != "") {
        i = reinterpret_cast<PVOID>(ui->lineEdit->text().toLong(&ok, 16));
    } else {
        i = nullptr;
    }

    pvAddress = VirtualAlloc(i, size.toInt() * 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if ( pvAddress != nullptr) {
        ui->lineEdit_4->setText("Try is successful");
        ui->listWidget_4->addItem(QString::number(reinterpret_cast<int>(pvAddress), 16) + " | " + size);
     } else {
        ui->lineEdit_4->setText("Try is failed");
     }
}

void MainWindow::on_pushButton_7_clicked() {
    QString param = ui->lineEdit->text() + " | " + ui->lineEdit_2->text();

    if(VirtualFree(reinterpret_cast<PVOID>(ui->lineEdit->text().toLong(&ok, 16)), 0, MEM_RELEASE)) {
        ui->lineEdit_4->setText("Free is successful");
        QList<QListWidgetItem *> found = ui->listWidget_4->findItems(param, Qt::MatchContains);
        for (QListWidgetItem *it : found) {
            delete ui->listWidget_4->takeItem(ui->listWidget_4->row(it));
        }
    } else {
        ui->lineEdit_4->setText("Free is failed");
    }
}

void MainWindow::on_pushButton_8_clicked() {
    QString str = ui->lineEdit_2->text();
    long i = ui->lineEdit->text().toLong(&ok, 16);

    if(WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(i), &str, sizeof(str), nullptr)) {
        ui->lineEdit_4->setText("Write is successful");
    } else {
        ui->lineEdit_4->setText("Write is failed");
    }
}

void MainWindow::on_pushButton_9_clicked() {
    QString str;
    long i = ui->lineEdit->text().toLong(&ok, 16);

    if(ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(i), &str, sizeof(str), nullptr)) {
        ui->lineEdit_4->setText("Read is successful");

        ui->listWidget_6->addItem(str);
    } else {
        ui->lineEdit_4->setText("Read is failed");
    }
}
