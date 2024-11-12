function onMonkeyClick(name, continents, image) {
    fetch(`https://en.wikipedia.org/w/api.php?origin=*&action=query&prop=extracts&format=json&exlimit=max&explaintext&exintro&titles=${encodeURIComponent(name)}`)
        .then(response => response.json())
        .then(data => {
            let pages = data.query.pages;
            let pageId = Object.keys(pages)[0];
            let description = pages[pageId].extract;

            let monkeyPageHtml = `
                <div class="monkey-detail">
                    <h1 class="monkey-detail__title">${name}</h1>
                    <div class="monkey-detail__image">
                        <img src="${image}" alt="${name}">
                    </div>
                    <div class="monkey-detail__description">${description}</div>
                    <p class="monkey-detail__continents">${continents}</p>
                    <button onclick="window.open('https://en.wikipedia.org/wiki/${encodeURIComponent(name)}', '_blank')" class="monkey-detail__wiki-button">More on wiki</button>
                </div>
            `;

            let mainContent = document.querySelector('.main__central-content');
            mainContent.innerHTML = monkeyPageHtml;
        })
        .catch(error => console.error('Error:', error));
}
