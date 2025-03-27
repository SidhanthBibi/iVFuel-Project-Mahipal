// index/api/data.js

export async function GET() {
  try {
    const url = process.env.KV_REST_API_URL;
    const token = process.env.KV_REST_API_TOKEN;

    const response = await fetch(`${url}/get/fuelData`, {
      method: "GET",
      headers: {
        Authorization: `Bearer ${token}`,
      },
      cache: "no-store",
    });

    if (!response.ok) {
      console.error("Failed fetching from Redis:", await response.text());
      return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 500 });
    }

    const { result } = await response.json();

    if (!result) {
      console.warn("No result returned from Redis.");
      return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 200 });
    }

    let parsed;
    try {
      parsed = JSON.parse(result);
    } catch (e) {
      console.error("Error parsing result JSON:", result);
      return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 500 });
    }

    const { flow, total } = parsed;
    return new Response(JSON.stringify({ flow, total }), { status: 200 });
  } catch (err) {
    console.error("GET /api/data error:", err);
    return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 500 });
  }
}
