document.addEventListener("DOMContentLoaded", () => {
    const formContato = document.getElementById("form-contato");
    if (formContato) {
        formContato.addEventListener("submit", (e) => {
            e.preventDefault();
            const nome = document.getElementById("nome").value;
            alert(`Obrigado, ${nome}! Seu interesse no curso Técnico em Informática do IFC Camboriú foi registrado com sucesso.`);
            formContato.reset();
        });
    }

    const btnBuscarApi = document.getElementById("btn-buscar-api");
    const paisInput = document.getElementById("pais-input");
    const apiResultado = document.getElementById("api-resultado");

    if (btnBuscarApi) {
        btnBuscarApi.addEventListener("click", async () => {
            const termoBusca = paisInput.value.trim();
            
            if (!termoBusca) {
                apiResultado.innerHTML = `<p style="color: red;">Por favor, digite o nome de um país.</p>`;
                return;
            }

            const urlAPI = `https://restcountries.com/v3.1/name/${encodeURIComponent(termoBusca)}`;

            apiResultado.innerHTML = `<p class="placeholder-text">Realizando requisição HTTP GET...</p>`;

            try {
                const resposta = await fetch(urlAPI);

                if (!resposta.ok) {
                    throw new Error(`Erro HTTP! Status: ${resposta.status} (${resposta.statusText})`);
                }

                const dados = await resposta.json();
                const pais = dados[0];

                apiResultado.innerHTML = `
                    <div style="display: flex; gap: 20px; align-items: center; flex-wrap: wrap;">
                        <img src="${pais.flags.svg}" alt="Bandeira" width="100" style="border: 1px solid #ccc; border-radius: 4px;">
                        <div>
                            <h4 style="color: var(--primary-color); margin-bottom: 5px;">${pais.name.common} (${pais.cca2})</h4>
                            <p><strong>Capital:</strong> ${pais.capital ? pais.capital[0] : 'N/A'}</p>
                            <p><strong>Região:</strong> ${pais.region} - ${pais.subregion || ''}</p>
                            <p><strong>População:</strong> ${pais.population.toLocaleString('pt-BR')} habitantes</p>
                        </div>
                    </div>
                `;

            } catch (erro) {
                console.error("Erro na requisição:", erro);
                apiResultado.innerHTML = `
                    <p style="color: #d32f2f; font-weight: bold;">Falha ao consultar a API.</p>
                    <p style="color: #555; font-size: 0.9rem;">Detalhes: ${erro.message}. Verifique se o nome do país está correto em inglês ou português.</p>
                `;
            }
        });
    }
});