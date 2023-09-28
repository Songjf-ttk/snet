import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

createApp(App).use(store).use(router).mount('#app')


/*
1. 从 vue 模块导入 createApp 方法。
2. 从 ./App.vue 导入 APP 组件。
3. 从 ./router 导入路由实例。
4. 从 ./store 导入 Vuex 状态管理存储。
5. 调用 createApp(App) 创建应用实例。
6. 在应用实例上调用 use(store) 挂载 Vuex 状态管理。
7. 调用 use(router) 挂载路由管理功能。
8. 最后调用 mount('#app') 把应用挂载到 #app 元素上。
*/