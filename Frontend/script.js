
document.addEventListener('DOMContentLoaded', () => {
  const container = document.getElementById('mainContainer');
  const runButton = document.getElementById('runButton');
  const outputDiv = document.getElementById('output');
  const addNewDiscussion = document.getElementById('addNewDiscussion');

  runButton.addEventListener('click', async () => {
    outputDiv.textContent = 'Hello, World!';
  });

  addNewDiscussion.addEventListener('click', () => {
    const node = document.createElement('div');
    node.style = 'background: grey;';
    node.className = 'box stack-top';
    node.innerHTML = 'goodby';
    container.appendChild(node);
  });

  
});