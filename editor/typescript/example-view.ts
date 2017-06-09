import * as stingray from 'stingray';

let mainContainer = document.querySelector('.main-container');
mainContainer.innerHTML =
    `<b>Stingray version:</b> ${stingray.env.version}<br/><br/>` +
    `<b>View URL:</b> <a>${document.URL}</a><br/>`;
