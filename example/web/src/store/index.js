import { createStore } from 'vuex'  //通过 import 语句导入 createStore 方法

export default createStore({  //使用 export default 导出一个通过 createStore 创建的 store 实例。
  state: {  //state 定义了状态对象,用于存储全局状态数据。
    username: null,
    account: 123456,
    islogin: false,
    grade:null,
    num:10
  },
  getters: {  //getters 用于定义基于 state 的 getter 计算属性。,
  },
  mutations: {  //mutations 定义了提交 mutation 更改状态的方法。
  },
  actions: {  //actions 中定义触发 mutation 的 action 方法。
  },
  modules: {  //modules 可以拆分为不同的模块,每模块都包含自己的 state、getters 等。

  }
})

/*
- state 状态管理
- getters 计算属性
- mutations 同步更新状态
- actions 异步触发 mutations
- modules 拆分多个 module
*/
