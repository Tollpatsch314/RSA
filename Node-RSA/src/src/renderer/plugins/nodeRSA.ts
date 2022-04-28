// Types Node-RSA
/// <reference path="../../../node_modules/@types/node-rsa/index.d.ts" />
const rsa = require("node-rsa");

let key = null;

export default class NodeRSA {
    private static _instance: NodeRSA = new NodeRSA();

    constructor() {
        if (NodeRSA._instance) return;
    }

    static getInstance(): NodeRSA {
        if (!NodeRSA._instance) NodeRSA._instance = new NodeRSA();
        return NodeRSA._instance;
    }

    public createRSA() {
        if(!key) {
            key = new rsa({b: 1024});
            key.setOptions({environment: 'browser', encryptionScheme: 'pkcs1', signingScheme: "pkcs1-sha512"});

        }

        return key;
    }

    public getRSA() {
        return key;
    }

    public removeRSA() {
        key = null;
    }
}