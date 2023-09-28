import { createRouter, createWebHistory } from 'vue-router'

import LoginView from '../views/LoginView.vue'
import Register from '../views/RegisterView.vue'
import SelectDifficulty from '../views/SelectDifficultyView.vue'
import EditPassword from '../views/EditPasswordView.vue'
import Problem from '../views/ProblemView.vue'
import GetMark from '../views/GetMarkView.vue'

const routes = [
  {
    path: '/',
    name: 'login',
    component: LoginView
  },
  {
    path: '/register',
    name: 'register',
    component: Register
  },
  {
    path: '/select_difficulty',
    name: 'select_difficulty',
    component: SelectDifficulty
  },
  {
    path: '/problem',
    name: 'problem',
    component: Problem
  },
  {
    path: '/edit_password',
    name: 'edit_password',
    component: EditPassword
  },
  {
    path: '/get_mark',
    name: 'get_mark',
    component: GetMark
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
