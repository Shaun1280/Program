const { app, BrowserWindow, Menu, ipcMain, dialog } = require('electron');
const url = require('url');
const path = require('path');

let mainWindow, insertWindow, nodeId, helpWindow = null;

// Listen for the app to be ready
app.on('ready', (): void => {
    // Create new window
    mainWindow = new BrowserWindow({
        width: 1280,
        height: 720,
        webPreferences:{
            nodeIntegration:true,
            contextIsolation: false,
            enableRemoteModule: true
        }
    });
    // Load html file into the window
    mainWindow.loadURL(url.format({
        pathname: path.join(__dirname, '../html/index.html'),
        protocol: 'file',
        slashes: true
    }));

    // Quite app when closed
    mainWindow.on('closed', (): void => {
        app.quit();
    });

    // Build menu from template
    const mainMenu = Menu.buildFromTemplate(mainMenuTemplate);
    mainWindow.setMenu(mainMenu);
    // Menu.setApplicationMenu(mainMenu);
});

// Handle create Insert window
function createInsertWindow(htmlUrl: string): void {
    // Create new window
    insertWindow = new BrowserWindow({
        width: 420,
        height: 280,
        title: 'Insert an element into linkedlist',
        webPreferences:{
            nodeIntegration:true,
            contextIsolation: false
        },
        resizable: false
    });
    // Load html file into the window
    insertWindow.loadURL(url.format({
        pathname: path.join(__dirname, htmlUrl),
        protocol: 'file',
        slashes: true
    }));

    insertWindow.setMenu(null);

    // Garbage collection handle
    insertWindow.on('close', (): void => {
        insertWindow = null;
    });
}

// Handle create help window
function createHelpWindow(): void {
    if (helpWindow != null) return;
    // Create new window
    helpWindow = new BrowserWindow({
        width: 900,
        height: 500,
        title: '帮助',
        webPreferences:{
            nodeIntegration:true,
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
    helpWindow.on('close', (): void => {
        helpWindow = null;
    });
}

ipcMain.on('node:rightClick', (e, item) => { // 右键菜单
    const contextMenu = Menu.buildFromTemplate(contextMenuTemplate);
    contextMenu.popup(BrowserWindow.fromWebContents(e.sender));
    nodeId = item;
})

ipcMain.on('node:insertAfterSubmit', (e, item) => { // 右键插入页面提交
    mainWindow.webContents.send('node:insertAfter', item, nodeId);
    insertWindow.close();
})

ipcMain.on('node:insertBeforeSubmit', (e, item) => { // 右键插入页面提交
    mainWindow.webContents.send('node:insertBefore', item, nodeId);
    insertWindow.close();
})

ipcMain.on('linkedlist:result', (e, item) => { // 用于操作结果提示
    dialog.showMessageBox({
        type: 'info',
        title: 'Message',
        message: item
    });
})

/* menu templates */
// Create contextmenu template
const contextMenuTemplate: any[] = [
    {
        label: 'Delete Node', // 删除右键节点
        click() {
            mainWindow.webContents.send('node:delete', nodeId);
        }
    }, {
        label: 'Insert After',
        click() {
            createInsertWindow('../html/InsertAfterWindow.html');
        }
    }, {
        label: 'Insert Before',
        click() {
            createInsertWindow('../html/InsertBeforeWindow.html');
        }
    }
];

// Create menu template
const mainMenuTemplate: any[] = [
    {
        label: 'File',
        submenu: [
            {
                label: 'New Single Linked List',
                accelerator: 'Shift+S',
                click() {
                    mainWindow.webContents.send('create:slist');
                }
            }, {
                label: 'New Doubly Linked List',
                accelerator: 'Shift+D',
                click() {
                    mainWindow.webContents.send('create:dlist');
                }
            }, {
                label: 'New Circular Linked LIst',
                accelerator: 'Shift+C',
                click() {
                    mainWindow.webContents.send('create:clist');
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
                    mainWindow.webContents.send('clear');
                }
            }, {
                label: 'Quit',
                accelerator: 'CommandOrControl+Q',
                click() {
                    app.quit();
                }
            }
        ]
    },
    {
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




