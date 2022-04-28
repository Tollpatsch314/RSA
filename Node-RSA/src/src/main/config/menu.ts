/**
 * Here is the place to define the menu, please check for details
 * Link: https://electronjs.org/docs/api/menu
 */

import { dialog } from 'electron'
import { type, arch, release } from 'os'
import packageInfo from '../../../package.json'
import { exec, spawn, execSync, spawnSync, execFileSync } from 'child_process';


function info() {
  dialog.showMessageBox({
    title: 'Info',
    type: 'info',
    message: 'RSA Tool (Encrypt / Decrypt / Generate)',
    detail: `Version Info: ${packageInfo.version}\nEngine Version：${
      process.versions.v8
    }\nCurrent System：${type()} ${arch()} ${release()}`,
    noLink: true,
  })
}

const menu = [
  {
    label: 'File',
    submenu: [
      {
        label: 'Reload',
        accelerator: 'F5',
        role: 'reload',
      },
      {
        label: 'Close',
        accelerator: 'CmdOrCtrl+F4',
        role: 'close',
      },
    ],
  },
  {
    label: 'Version',
    submenu: [
      {
        label: 'About',
        click: function () {
          info()
        },
      },
    ],
  },
  // {
  //   label: 'Test',
  //   submenu: [
  //     {
  //       label: '1_Erzeugung.exe',
  //       click: function () {
  //           const thread = spawn('1_Erzeugung.exe', [], {
  //               detached: true,
  //               stdio: 'ignore',
  //           });
  //       },
  //     },
  //     {
  //       label: '2_Verschluesselung.exe',
  //       click: function () {
  //         const thread = spawn('2_Verschluesselung.exe', [], {
  //             detached: true,
  //             stdio: 'ignore',
  //         });
  //       },
  //     },
  //     {
  //       label: '3_Entschluesselung.exe',
  //       click: function () {
  //           const thread = spawn('3_Entschluesselung.exe', [], {
  //               detached: true,
  //               stdio: 'ignore',
  //           });
  //       },
  //     },
  //   ],
  // },
]

export default menu
