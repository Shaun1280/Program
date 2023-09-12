const PatientManageSystem = require("./classes/PatientManageSystem.js");
const { app, BrowserWindow, Menu, ipcMain, dialog, ipcRenderer } = require('electron');
const url = require('url');
const path = require('path');
// process.env.NODE_ENV = 'production';
let patientManageSystem = new PatientManageSystem(); // 病人管理系统
let mainWindow, historyPatientTable = null, helpWindow = null;
// Listen for the app to be ready
app.on('ready', () => {
    // Create new window
    mainWindow = new BrowserWindow({
        width: 1600,
        height: 1000,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true
        },
        resizable: false
    });
    // Load html file into the window
    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '../html/index.html'),
        protocol: 'file',
        slashes: true
    }));
    // Quite app when closed
    mainWindow.on('closed', () => {
        app.quit();
    });
    // Build menu from template
    const mainMenu = Menu.buildFromTemplate(mainMenuTemplate);
    mainWindow.setMenu(mainMenu);
    // Menu.setApplicationMenu(mainMenu);
    mainWindow.maximize();
});
// Handle create 历史病人表窗口
function createHistoryPatientTable() {
    // Create new window
    historyPatientTable = new BrowserWindow({
        width: 800,
        height: 600,
        title: 'Treatment History Table',
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        },
        alwaysOnTop: true,
        resizable: false
    });
    // Load html file into the window
    historyPatientTable.loadURL(url.format({
        pathname: path.join(__dirname, "../html/patientTable.html"),
        protocol: 'file',
        slashes: true
    }));
    historyPatientTable.setMenu(null);
    // Garbage collection handle
    historyPatientTable.on('close', () => {
        historyPatientTable = null;
    });
}
// Handle create help window
function createHelpWindow() {
    if (helpWindow != null)
        return;
    // Create new window
    helpWindow = new BrowserWindow({
        width: 900,
        height: 500,
        title: '帮助',
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        },
        resizable: false,
        alwaysOnTop: true
    });
    // Load html file into the window
    helpWindow.loadURL(url.format({
        pathname: path.join(__dirname, "../html/help.html"),
        protocol: 'file',
        slashes: true
    }));
    helpWindow.setMenu(null);
    // Garbage collection handle
    helpWindow.on('close', () => {
        helpWindow = null;
    });
}
// Create menu template
const mainMenuTemplate = [
    {
        label: 'File',
        submenu: [
            {
                label: '普通科室候/就诊列表',
                accelerator: 'CommandOrControl+D',
                click() {
                    mainWindow.loadURL(url.format({
                        pathname: path.join(__dirname, '../html/index.html'),
                        protocol: 'file',
                        slashes: true
                    }));
                }
            }, {
                label: 'B 超室候/就诊列表',
                accelerator: 'CommandOrControl+B',
                click() {
                    mainWindow.loadURL(url.format({
                        pathname: path.join(__dirname, '../html/ultrasound_index.html'),
                        protocol: 'file',
                        slashes: true
                    }));
                }
            }, {
                label: '挂号',
                submenu: [
                    {
                        label: '添加就诊人',
                        accelerator: 'CommandOrControl+N',
                        click() {
                            mainWindow.loadURL(url.format({
                                pathname: path.join(__dirname, '../html/addPatient.html'),
                                protocol: 'file',
                                slashes: true
                            }));
                        }
                    }, {
                        label: '随机添加',
                        accelerator: 'CommandOrControl+P',
                        click() {
                            mainWindow.loadURL(url.format({
                                pathname: path.join(__dirname, '../html/randomAddPatient.html'),
                                protocol: 'file',
                                slashes: true
                            }));
                        }
                    }
                ]
            }, {
                label: '科室',
                accelerator: 'CommandOrControl+K',
                click() {
                    mainWindow.loadURL(url.format({
                        pathname: path.join(__dirname, '../html/department.html'),
                        protocol: 'file',
                        slashes: true
                    }));
                }
            }, {
                label: '查找',
                accelerator: 'CommandOrControl+F',
                click() {
                    mainWindow.webContents.send("page:find");
                }
            }, {
                label: 'Clear',
                accelerator: 'CommandOrControl+E',
                click() {
                    dialog.showMessageBox({
                        type: 'warning',
                        title: 'Message',
                        message: "是否清空所有信息？",
                        buttons: ["否", "是"]
                    }).then((index) => {
                        if (index.response == 1) {
                            patientManageSystem = new PatientManageSystem();
                            if (historyPatientTable != null)
                                historyPatientTable.close();
                            mainWindow.reload();
                        }
                    });
                }
            }, {
                label: 'Quit',
                accelerator: 'CommandOrControl+Q',
                click() {
                    app.quit();
                }
            }
        ]
    }, {
        label: 'View',
        submenu: [
            { role: 'reload' },
            { role: 'forceReload' },
            { role: 'toggleDevTools' },
            { type: 'separator' },
            { role: 'resetZoom' },
            { role: 'zoomIn' },
            { role: 'zoomOut' },
            { type: 'separator' },
            { role: 'togglefullscreen' }
        ]
    },
    {
        label: 'Window',
        submenu: [
            { role: 'minimize' },
            { role: 'zoom' },
            ...(process.platform == "darwin" ? [
                { type: 'separator' },
                { role: 'front' },
                { type: 'separator' },
                { role: 'window' }
            ] : [
                { role: 'close' }
            ])
        ]
    }, {
        label: 'help',
        click() { createHelpWindow(); }
    }
];
/* menu templates */
// 以下为事件监听
// 挂号 dialog 弹窗提示
ipcMain.on('register:error-message', (e, item) => {
    dialog.showMessageBox({
        type: 'warning',
        title: 'Message',
        message: item,
    });
});
ipcMain.on('register:success-message', (e, item) => {
    dialog.showMessageBox({
        type: 'info',
        title: '挂号成功',
        message: item + ", 是否留在当前界面？",
        buttons: ["是", "否"]
    }).then((index) => {
        if (index.response === 1) { // 返回叫号页面
            mainWindow.loadURL(url.format({
                pathname: path.join(__dirname, '../html/index.html'),
                protocol: 'file',
                slashes: true
            }));
        }
    });
});
/** 总病人列表更新
 */
// 1. 表单提交，并向主页面发送信息 (index.html 接受)
// 2. 主页面 (index.html)
let _department, _doctor;
ipcMain.on("patientlist:register", (e, item) => {
    patientManageSystem.patientRegister(item);
    mainWindow.webContents.send("patientlist:update_index", patientManageSystem.getPatientList());
});
// 发送普通科室总排队列表
ipcMain.on("patientlist:update", (e) => {
    mainWindow.webContents.send("patientlist:update_index", patientManageSystem.getPatientList());
});
// 发送B 超室总病人列表
ipcMain.on("patientlist:ultra_update", (e) => {
    mainWindow.webContents.send("patientlist:ultra_update_index", patientManageSystem.getUltrasoundPatientList());
});
// 以上为总病人列表更新
/** 医生监听
 */
function updateHistoryWindow() {
    if (historyPatientTable != null) { // 若医生病人列表窗口打开，则不新建窗口，而是更新病人信息
        let array = patientManageSystem.getDepartment(_department).getDoctor(_doctor).getHistoryPatientList();
        historyPatientTable.webContents.send("doctor:showHistoryPatientList", _department, _doctor, array);
    }
}
// 1. 取下一个病人
ipcMain.on("doctor:next_patient", (e, department, doctor) => {
    if (patientManageSystem.getDepartment(department).getDoctor(doctor).isBusy()) {
        dialog.showMessageBox({
            type: 'warning',
            title: 'Message',
            message: "请点击就诊完成后再接收下一个病人！",
        });
        return;
    }
    if (patientManageSystem.getDepartment(department).getDoctor(doctor).getNextPatient() == null) {
        dialog.showMessageBox({
            type: 'info',
            title: 'Message',
            message: "暂无等候病人",
        });
        return;
    }
    patientManageSystem.getDepartment(department).getDoctor(doctor).treatNextPatient();
    patientManageSystem.getDepartment(department).allocatePatient();
    // 修改总病人列表
    let currentPatient = patientManageSystem.getDepartment(department).getDoctor(doctor).getCurrentPatient();
    patientManageSystem.reorderTreatingPatient(currentPatient);
    // 更新医生状态
    let doctorStatus = patientManageSystem.getDepartment(department).getDoctor(doctor).getStatus();
    mainWindow.webContents.send("doctor:status", department, doctor, doctorStatus);
    // 更新科室列表
    let displayedPatient = patientManageSystem.getDepartment(department).getDisplayedPatient();
    mainWindow.webContents.send("department:displayedPatient", department, displayedPatient);
    // 如果历史病人窗口打开 更新
    updateHistoryWindow();
});
// 2. 完成诊断监听
ipcMain.on("doctor:done", (e, department, doctor) => {
    if (!patientManageSystem.getDepartment(department).getDoctor(doctor).isBusy()) {
        dialog.showMessageBox({
            type: 'info',
            title: 'Message',
            message: "暂无正在诊断的病人",
        });
        return;
    }
    patientManageSystem.getDepartment(department).getDoctor(doctor).done();
    // 诊断结束后再分配新病人
    patientManageSystem.getDepartment(department).allocatePatient();
    // 修改总病人列表
    let leavePatient = patientManageSystem.getDepartment(department).getDoctor(doctor).getLeavePatient();
    patientManageSystem.removeLeavingPatient(leavePatient);
    // 加入 B 超室病人
    if (leavePatient.bTag == true) {
        if (leavePatient.bTreatmentTime == "") {
            patientManageSystem.ultrasoundPatientRegister(leavePatient);
            // 更新 B 超室状态
            for (let i = 1; i <= 3; i++) {
                let doctorStatus = patientManageSystem.getDepartment(16).getDoctor(i).getStatus();
                mainWindow.webContents.send("doctor:status", 16, i, doctorStatus);
            }
            let displayedPatient = patientManageSystem.getDepartment(16).getDisplayedPatient();
            mainWindow.webContents.send("department:displayedPatient", 16, displayedPatient);
        }
        else if (leavePatient.endTime == "") { // 从 B 超室返回的病人 还未结束诊断
            let retDep = leavePatient.department, retDoc = leavePatient.doctorid;
            patientManageSystem.getDepartment(retDep).getDoctor(retDoc).enqueReturnPatient(leavePatient);
            patientManageSystem.getDepartment(retDep).allocatePatient();
            // 更新原科室状态 科室列表不用更新
            let doctorStatus = patientManageSystem.getDepartment(retDep).getDoctor(retDoc).getStatus();
            mainWindow.webContents.send("doctor:status", retDep, retDoc, doctorStatus);
        }
    }
    // 更新医生状态
    let doctorStatus = patientManageSystem.getDepartment(department).getDoctor(doctor).getStatus();
    mainWindow.webContents.send("doctor:status", department, doctor, doctorStatus);
    // 更新科室列表
    let displayedPatient = patientManageSystem.getDepartment(department).getDisplayedPatient();
    mainWindow.webContents.send("department:displayedPatient", department, displayedPatient);
    // 如果历史病人窗口打开 更新
    updateHistoryWindow();
});
// 3. 开具 B 超
ipcMain.on("doctor:ultrasound", (e, department, doctor) => {
    let currentPatient = patientManageSystem.getDepartment(department).getDoctor(doctor).getCurrentPatient();
    if (currentPatient == null) {
        dialog.showMessageBox({
            type: 'warning',
            title: 'Message',
            message: "暂无正在诊断的病人",
        });
        return;
    }
    if (currentPatient.bTag == true) {
        if (currentPatient.bTreatmentTime == "") {
            dialog.showMessageBox({
                type: 'info',
                title: 'Message',
                message: "已为该病人开具 B 超，是否取消？",
                buttons: ["否", "是"]
            }).then((index) => {
                if (index.response == 1) {
                    currentPatient.bTag = false;
                    // 如果历史病人窗口打开 更新
                    updateHistoryWindow();
                }
            });
        }
        else {
            dialog.showMessageBox({
                type: 'warning',
                title: 'Message',
                message: "该病人已做过 B 超检查!"
            });
        }
        return;
    }
    // 设置开具 B 超
    patientManageSystem.getDepartment(department).getDoctor(doctor).setUltraSoundTag();
    // 如果历史病人窗口打开 更新
    updateHistoryWindow();
    // 发送提示
    dialog.showMessageBox({
        type: 'info',
        title: 'Message',
        message: "开具 B 超成功",
    });
});
// 4. 新建病人历史表窗口
ipcMain.on("doctor:historyPatientList", (e, department, doctor) => {
    _department = department, _doctor = doctor;
    if (historyPatientTable == null)
        createHistoryPatientTable(); // 新建病人列表窗口
    else
        updateHistoryWindow(); // 窗口已弹出，则只更新内容
});
// 5. 新窗口载入事件触发，发送历史病人表信息
ipcMain.on("patientTalbe:load", (e) => { updateHistoryWindow(); });
// 以上为医生事件监听
/** 科室监听
 *
 */
// 1. 科室页面加载监听
ipcMain.on("department:load", (e) => {
    for (let department = 1; department <= 16; department++) {
        for (let doctor = 1; doctor <= 3; doctor++) {
            let doctorStatus = patientManageSystem.getDepartment(department).getDoctor(doctor).getStatus();
            mainWindow.webContents.send("doctor:status", department, doctor, doctorStatus);
        }
        // 更新科室病人列表
        let displayedPatient = patientManageSystem.getDepartment(department).getDisplayedPatient();
        // console.log("departmetn: " + department, displayedPatient.length);
        mainWindow.webContents.send("department:displayedPatient", department, displayedPatient);
    }
});
// 以上是科室监听
