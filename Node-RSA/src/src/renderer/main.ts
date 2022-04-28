import { createApp } from 'vue'

import App from './App.vue'
import router from './router'
import './router/guard'
import './assets/styles/global.css'

const app = createApp(App)
app.use(router).mount('#app')
