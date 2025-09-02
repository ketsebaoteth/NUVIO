import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "NUVIO / docs",
  description: "nuvio codebase guide.",
  themeConfig: {
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Docs', link: '/thankyou' }
    ],

    sidebar: [
      {
        text: 'Core',
        items: [
          { text: 'Components', link: '/components.md' },
        ]
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/ketsebaoteth/nuvio' }
    ]
  }
})
