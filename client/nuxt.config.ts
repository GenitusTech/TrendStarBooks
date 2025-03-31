// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  compatibilityDate: '2024-11-01',
  devtools: { enabled: import.meta.env.DEV },

  app: {
    layoutTransition: { name: 'layout', mode: 'out-in' },
    pageTransition: { name: 'page', mode: 'out-in' }
  },
  srcDir: './src',
  typescript: {
    strict: true,
    builder: 'vite',
    typeCheck: true,
    shim: true
  },
  nitro: {},
  postcss: {},
  vite: {
    vue: {}
  },
  routeRules: {
    '/rss.xml': {prerender: true}
  },
  modules: []
})
