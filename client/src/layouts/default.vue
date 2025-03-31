<script setup lang="ts">
defineOptions({
    name: 'layout-default'
})
</script>

<template>
    <div>
        <header>HEADER</header>
        <main>
            MAIN
            <slot></slot>
        </main>
        <footer>FOOTER</footer>
    </div>
</template>

<style lang="scss" scoped>
//
</style>