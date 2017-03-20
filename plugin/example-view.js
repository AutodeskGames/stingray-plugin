define(require => {
    const stingray = require('stingray');

    let mainContainer = document.querySelector('.main-container');
    console.assert(mainContainer);
    mainContainer.innerHTML =
        `<b>Stingray version:</b> ${stingray.env.version}<br/><br/>` +
        `<b>View URL:</b> <a>${document.URL}</a><br/>`;
})
