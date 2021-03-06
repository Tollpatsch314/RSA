'use strict'

import { app } from 'electron'

import InitWindow from './services/windowManager'
import { disableDevModeFromKeyboard } from './config/disable'
import MainInit from './services/windowManager';
import ipcEvents from './services/ipcEvents';

let window: MainInit = null;

function onAppReady() {
  window = new InitWindow();
  window.initWindow();
  disableDevModeFromKeyboard();

  // Register IpcMain
  ipcEvents.init();
}

app.isReady() ? onAppReady() : app.on('ready', onAppReady)

// Due to the 9.x version issue, you need to add this configuration to close the cross-domain issue
app.commandLine.appendSwitch('disable-features', 'OutOfBlinkCors')

app.on('window-all-closed', () => {
  // All platforms exit the software when all windows are closed
  app.quit()
})
app.on('browser-window-created', () => {
  console.log('Window Created')
})

if (process.defaultApp) {
  if (process.argv.length >= 2) {
    app.removeAsDefaultProtocolClient('electron-vue-template')
    console.log(
      'Cannot be used in the development environment due to the particularity of the framework'
    )
  }
} else {
  app.setAsDefaultProtocolClient('electron-vue-template')
}