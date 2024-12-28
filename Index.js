const mainContainer = document.getElementById('mainContainer');
const singlePlayerContainer = document.getElementById('singlePlayerContainer');
const multiplePlayerContainer = document.getElementById('multiplePlayerContainer');
const optionContainer = document.getElementById('optionContainer');

const buttons = document.querySelectorAll('.button');

function playClickSound() {
    const clickSound = document.getElementById('clickSound');
    clickSound.currentTime = 0;
    clickSound.play();
}

buttons.forEach(button => {
    button.addEventListener('click', (e) => {
        playClickSound();

        if (e.target.id === 'singlePlayerButton') {
            toggleContainers(mainContainer, singlePlayerContainer);
        } else if (e.target.id === 'multiplePlayerButton') {
            toggleContainers(mainContainer, multiplePlayerContainer);
        } else if (e.target.id === 'optionButton') {
            toggleContainers(mainContainer, optionContainer);
        } else if (e.target.classList.contains('finishButton')) {
            // 根据当前显示的容器确定要返回的容器
            if (!singlePlayerContainer.classList.contains('hidden')) {
                toggleContainers(singlePlayerContainer, mainContainer);
            } else if (!multiplePlayerContainer.classList.contains('hidden')) {
                toggleContainers(multiplePlayerContainer, mainContainer);
            } else if (!optionContainer.classList.contains('hidden')) {
                toggleContainers(optionContainer, mainContainer);
            }
        }
    });
});

function toggleContainers(hideContainer, showContainer) {
    hideContainer.classList.add('hidden');
    showContainer.classList.remove('hidden');
}
